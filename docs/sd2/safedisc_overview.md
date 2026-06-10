# SafeDisc 2.x Decryption Overview

Reference for the offline decryptor.  Assumes the reader has the
protected binary (e.g. `runblack.exe`) and the on-disc artifacts
that ship with it (`secdrv.sys`, `drvmgt.dll`); does NOT assume any
workspace-local capture files.

For chronological investigation notes see [safedisc_tea_key.md].

---

## High-level architecture

A SafeDisc 2.x release wraps a Win32 PE with an obfuscated loader
(`sd_loader`) that, at process startup, decrypts the original .text
and .rdata sections back into memory and jumps to the original
entry point.  The loader uses a kernel-mode helper driver
(`secdrv.sys`) for authorization only; the bulk decryption is
entirely user-mode.

A wrapped PE has three encrypted regions:

| Region | Notes |
|---|---|
| Original `.text` (code)   | Bulk-decrypted in 4 KB chunks at runtime. |
| Original `.rdata` (rodata) | Same cipher; tail-end of the same decrypt pass. |
| sd_loader stubs themselves | Self-decrypting layers (see "Self-modifying code"). |

The loader code lives within the .text VA range with a sliding
base of `sd_base + ~0x1000`.  `sd_base` is the runtime VA the loader
ends up at after relocation; it varies per run and is not stored on
disk.  All sd_loader offsets below are relative to `sd_base`.

---

## Two decryption paths

### Path A: ORIGINAL (in-process at runtime)

```
runblack.exe starts
   |
   v
[1] sd_loader self-decrypt (multi-stage)
   - Loader code arrives on disk in encrypted form
   - Each stage unpacks the next stage of loader code in memory
   - SELF-MODIFYING; see below
   - Stage count: at least 2 distinct states are observed
     (on-disk encrypted form, runtime decrypted form in the
     0x1d000..0x1e000 region, differing by ~98% of bytes).
     Whether additional intermediate stages exist between
     these two end-points has not been mapped -- would require
     additional memory snapshots at earlier instr-count checkpoints.
   |
   v
[2] secdrv handshake
   - A small number of NtDeviceIoControlFile calls to \\.\secdrv
   - Observed count in one full cipher window: 14
   - Authorization handshake only.  Not on the per-block path.
   - Per-IOCTL semantics (IOCTL codes, in/out buffer sizes) not yet
     captured.  Plan: extend cipher_trace to hook the syscall entry
     for NtDeviceIoControlFile (syscall index 0x6f on Win7 x86) and
     dump IoControlCode + InputBuffer / OutputBuffer for each.
   |
   v
[3] Key derivation
   - "key_post" (16 bytes) materializes at a target-process VA
     `dw_bec` chosen by the loader.
   - The derivation step that PRODUCES key_post lives inside earlier
     sd_loader stages (the still-self-decrypting portion above);
     that step has not been traced.  Its input could be (a) an
     encrypted blob inside the PE header / loader stubs, (b) data
     returned from the secdrv IOCTLs, or (c) a mix.  Until traced,
     key_post is treated as an opaque value captured at runtime.
   - The post-derivation step (key_post -> tea_key) IS traced and is
     a 32-bit XOR per dword against the constant 0x89E0AD7D (see
     "SD-KDF magic" below for the universality question).
     `tea_key = key_post XOR (0x89E0AD7D repeated x4)`.
   |
   v
[4] Pre-transform per 4 KB chunk
   - Function entry: sd_base + 0x1d828
   - Allocates a 4 KB stack staging buffer at [ebp - 0x1020]
   - Reads the encrypted chunk into staging via the wrapper at
     sd_base + 0x1d6e0
   - Runs the inner per-byte transform (SDS-PT, defined below)
   |
   v
[5] TEA decrypt over the staging
   - TEA entry: sd_base + 0x2FCA
   - Standard 32-round TEA, delta 0x9E3779B9
   - Decrypts each 8-byte block of the staging in place
   |
   v
[6] Copy staging to the target's .text VA range
   - Helper at sd_base + 0x1d6e0 calls an imported function
     ([0x1004c734]) which emits the decrypted bytes into the
     real PE section memory
   |
   v
Target .text now plaintext.  sd_loader jumps to the original entry
point.
```

### Path B: OFFLINE (`tools/sd2decrypt/`)

```
Input: protected runblack.exe on disk
   |
   v
[1] Parse PE, locate the .text section bytes (encrypted form)
[2] Compute tea_key = key_post XOR (0x89E0AD7D x4)
       where key_post is either:
         (a) supplied on cmdline (--key-post)
         (b) extracted live once via the cleaner under PANDA, then
             reused offline.
       A fully-offline path -- deriving key_post from PE bytes without
       any runtime -- requires identifying the sd_loader stage that
       produces key_post.  That stage is in the still-self-decrypting
       region above (item [3] in path A) and has not been traced.
       Until then key_post is treated as an externally-supplied opaque
       128-bit input to the offline tool.
[3] For each 4 KB chunk of .text (chunks are independent across chunks
    and the per-dword path is independent within a chunk -- fully
    parallelizable):
       interpret chunk as 1024 LE u32 dwords
       SDS-BPT pass 0: dwords[i] = pass0(dwords[i] ^ counter_mask(i))
       SDS-BPT pass 1: dwords[i] = pass1(dwords[i] ^ counter_mask(i))
       for each 8-byte block in the chunk (512 blocks, parallel):
           TEA_decrypt(block, tea_key)
[4] Repeat (3) for .rdata
       Empirically the encrypted and decrypted .rdata images are the
       same length (no expansion / no header) and chunk-aligned the
       same way as .text, so the same SDS-PT + TEA pass covers the
       whole section.  Strings and read-only globals visible in the
       decrypted form span the full section range -- no observed
       plaintext gap.  This still wants end-to-end cross-check.
[5] Rebuild PE (drop sd_loader stubs, fix imports, fix indirect
    calls / jump tables, fix section sizes -- existing logic lives
    in patches_fn.rs in the Windows-only cleaner)
[6] Write SD2cleaned.exe
```

Step (3) reproduces the runtime ciphertext-to-TEA-input mapping
exactly.  See "SDS-BPT" below.

---

## Keys and constants

### TEA key (128 bits)

The actual cipher key for the bulk decrypt.

```
Per-binary.  Sample value for runblack.exe:

  raw bytes : b2 1c 62 72 ae 99 17 92 22 4d ca 02 8a b1 b7 83
  as 4 u32  : k0=0x72621cb2  k1=0x921799ae
              k2=0x02ca4d22  k3=0x83b7b18a
```

**Different per protected binary.**  Obtainable two ways:
- Directly by capture under PANDA (or equivalent dynamic-analysis
  setup that can observe live memory at the BP3 trap point).
- Indirectly via `key_post` plus the SD-KDF magic.  If both inputs
  are obtainable for a given binary without running it, so is the
  TEA key.

A fully-static path requires identifying the sd_loader stage that
produces key_post from PE bytes (see "Missing pieces").

### key_post (128 bits, intermediate)

Materialized by sd_loader at a per-run target VA `dw_bec`.  The
cleaner captures it by trapping a write at sd_base + 0x4D02 (the
"BP3" trap) and reading 16 bytes from `dw_bec` right before the
trap is released.

```
key_post = tea_key XOR (0x89E0AD7D repeated x4)
```

Obtainable without PANDA only if the sd_loader stage that produces
key_post is identified and ported (currently not -- that stage is
inside the still-self-decrypting layers of sd_loader).  In principle
the input to that derivation lives entirely in the PE file (probably
combined with a constant or two), so a fully-static recovery is not
foreclosed -- it is unanalyzed.

### SD-KDF magic (32 bits)

```
Value: 0x89E0AD7D  (verified for runblack.exe)
```

Used in: `tea_key[i] = key_post[i] XOR 0x89E0AD7D` for each of four
32-bit dwords.

**Provenance.**  Identified by sampling memory transitions at
`dw_bec` across one cleaner replay under PANDA: the difference
between successive values of the staging dword and the final
key_post dword resolved to this constant, repeated.

**Universality.**  Single point of evidence.  Could be (a) a
per-binary constant baked into sd_loader (different per release),
(b) a SafeDisc-2-wide constant (same across all releases), or (c)
a per-binary value computed from another input.  Resolving this
requires running the same capture against at least one additional
SafeDisc 2 release and comparing.  Hardcoding 0x89E0AD7D in the
offline tool will work for runblack.exe today; the offline tool
should keep it as a command-line override until verified.

### SDS-PT constants (8-bit each)

```
byte-0 initial XOR     : 0x43   at PC sd_base + 0x1d915
running-key seed XOR   : 0x15   at PC sd_base + 0x1d942
chunk size cap         : 0x1000 at PC sd_base + 0x1d8a3 / d8b7
```

---

## Algorithms (named)

### SDS-BPT (SafeDisc Bulk Pre-Transform)

A 2-pass keystream-XOR + fixed-function-mix transform applied to
each 4 KB chunk of encrypted .text / .rdata before TEA decrypt.
Dispatcher function at `sd_base + 0x1b69e`; transform target is the
64-bit-block input stream consumed by TEA.

**Per-chunk shape.**  Input is one 4 KB chunk treated as 1024 LE
u32 dwords.  Output is the same length (in place).  All 1024 dwords
in a pass are **independent** -- the handler is a pure function of
its EAX input with no inter-dword state.  Pass 1 depends on Pass 0
(reads Pass 0's output of the same dword).  Across chunks: no
state -- each 4 KB chunk decrypts independently.

#### Pseudocode

```c
void sds_bpt(uint32_t *buf, size_t n_dwords) {       // n_dwords = 1024 for 4 KB
    for (size_t i = 0; i < n_dwords; i++)
        buf[i] = pass0(buf[i] ^ counter_mask(i));
    for (size_t i = 0; i < n_dwords; i++)
        buf[i] = pass1(buf[i] ^ counter_mask(i));
}
```

#### Counter mask

Per-iteration the dword is XOR'd with a counter-derived mask
constructed by replicating low bytes of `i` across four lanes via
shift-OR with **32-bit overflow on each shift** (NOT a plain
`i * 0x01010101` multiplication):

```c
static inline uint32_t counter_mask(uint32_t i) {
    return  ((i << 24) & 0xFFFFFFFFu)
          | ((i << 16) & 0xFFFFFFFFu)
          | ((i <<  8) & 0xFFFFFFFFu)
          |  (i        & 0xFFFFFFFFu);
}
```

For `i < 256` this collapses to `i * 0x01010101` (byte i broadcast to
all 4 lanes).  For `i >= 256` the high bits of `i` leak across lanes
because each shift is truncated to 32 bits before the ORs combine.
Reimplementations must use the shift-OR form or otherwise
bit-exactly match it (the multiplicative form is wrong for `i >=
256`, which IS reached every chunk since `n_dwords = 1024`).

#### Pass 0 (handler at `sd_base + 0x1b30e`, 99 bytes)

Applied left-to-right to EAX; final EAX is the dword output.  No
memory access, EAX is the only register touched.

| #  | Op             | Imm        |
|----|----------------|------------|
| 1  | ROL EAX, n     | 1          |
| 2  | XOR EAX, imm32 | 0x22CF7543 |
| 3  | SUB EAX, imm32 | 0x4C1A091B |
| 4  | SUB EAX, imm32 | 0x3ECF00FC |
| 5  | XOR EAX, imm32 | 0x4A745317 |
| 6  | ROR EAX, n     | 6          |
| 7  | ADD EAX, imm32 | 0x33992991 |
| 8  | SUB EAX, imm32 | 0x3B08421D |
| 9  | ROL EAX, n     | 2          |
| 10 | ROR EAX, n     | 0 (no-op)  |
| 11 | XOR EAX, imm32 | 0x28143E25 |
| 12 | ROL EAX, n     | 3          |
| 13 | XOR EAX, imm32 | 0x2C08711A |
| 14 | SUB EAX, imm32 | 0x145A7207 |
| 15 | ADD EAX, imm32 | 0x22F12A73 |
| 16 | XOR EAX, imm32 | 0x76C36F07 |
| 17 | ROL EAX, n     | 28         |
| 18 | ADD EAX, imm32 | 0x563326D0 |
| 19 | ROL EAX, n     | 26         |
| 20 | XOR EAX, imm32 | 0x71427E58 |
| 21 | XOR EAX, imm32 | 0x7DD315D8 |
| 22 | SUB EAX, imm32 | 0x49CA69D6 |

Rotate counts shown are already `imm8 & 0x1F` (x86 masks rotate
counts to 5 bits for 32-bit operands; the raw bytecode encodes
0x21, 0x82, 0x80, 0x1C, 0xDA which mask to 1, 2, 0, 28, 26).
Step 10 is a `ROR EAX, 0x80` whose effective count is 0 -- it does
nothing and can be elided.

#### Pass 1 (handler at `sd_base + 0x1b371`, 99 bytes)

Same calling convention as Pass 0.

| #  | Op             | Imm        |
|----|----------------|------------|
| 1  | INC EAX        |            |
| 2  | ADD EAX, imm32 | 0x71531BF9 |
| 3  | SUB EAX, imm32 | 0x678D4FFA |
| 4  | ROR EAX, n     | 6          |
| 5  | ADD EAX, imm32 | 0x1D715839 |
| 6  | XOR EAX, imm32 | 0x3EF04020 |
| 7  | ADD EAX, imm32 | 0x06C30F66 |
| 8  | DEC EAX        |            |
| 9  | INC EAX        |            |
| 10 | ADD EAX, imm32 | 0x10222BAF |
| 11 | INC EAX        |            |
| 12 | ROL EAX, n     | 30         |
| 13 | SUB EAX, imm32 | 0x03B17BD3 |
| 14 | XOR EAX, imm32 | 0x719922CF |
| 15 | INC EAX        |            |
| 16 | INC EAX        |            |
| 17 | NEG EAX        |            |
| 18 | ROL EAX, n     | 12         |
| 19 | ADD EAX, imm32 | 0x3D183399 |
| 20 | DEC EAX        |            |
| 21 | ROR EAX, n     | 22         |
| 22 | NEG EAX        |            |
| 23 | ROL EAX, n     | 20         |
| 24 | ROL EAX, n     | 26         |
| 25 | ROR EAX, n     | 8          |
| 26 | NEG EAX        |            |
| 27 | INC EAX        |            |
| 28 | INC EAX        |            |
| 29 | ROR EAX, n     | 20         |
| 30 | ROL EAX, n     | 19         |
| 31 | ROL EAX, n     | 25         |
| 32 | DEC EAX        |            |
| 33 | ROL EAX, n     | 11         |
| 34 | ROL EAX, n     | 0 (no-op)  |
| 35 | DEC EAX        |            |

Raw rotate-count bytes 0xFE, 0x6C, 0x36, 0x14, 0x7A, 0x08, 0x54,
0x33, 0x59, 0x8B, 0x80 mask to 30, 12, 22, 20, 26, 8, 20, 19, 25,
11, 0.  Step 34 is the `ROL EAX, 0x80` no-op.  `INC`/`DEC` runs
(steps 8-9 and 15-16) can be fused: net effect of 8+9 is zero; 15+16
adds 2; 27+28 adds 2.

NEG, INC, DEC are integer ops on the full 32-bit EAX with x86
semantics (`NEG x` = `0 - x` mod 2^32; `INC` / `DEC` are += 1 / -= 1
mod 2^32 -- they do NOT modify CF, but since the handler has no
conditional branches and only the final EAX is observed, flag side
effects do not matter).

#### Sources of the bytecode

`pass0` and `pass1` are static `.text` bytes inside `sd_loader`,
NOT generated or copied at runtime.  Verified by re-snapping the
handler region (`sd_base + 0x1b300 .. 0x1b400`) at the moment of
first dispatch entry: bytes are identical to the cipher-window
snapshot.  No self-modification in this region.

#### Parallelism notes (for SIMD / multithreading)

- **Inter-chunk**: chunks are fully independent.  Process all
  N 4 KB chunks in parallel.  No state crosses chunks.
- **Intra-pass**: each dword in a pass is an independent pure
  function of (its input dword, its index `i`).  Within Pass 0 or
  within Pass 1, all 1024 dwords are independently computable.
  SIMD lanes can process N dwords in parallel as long as the
  per-dword `i` is supplied (each lane gets a distinct counter).
- **Pass ordering**: Pass 1 reads Pass 0's outputs of the same
  dword -- Pass 0 must complete before Pass 1 for that dword
  (per-dword sequential, not per-buffer).  Trivial sync: do all
  of Pass 0 then all of Pass 1.  A streaming pipeline can also
  overlap them at dword granularity.
- **No flag dependence**: NEG / INC / DEC effects on flags are
  unused.  Lane-parallel implementations don't need to model EFLAGS.
- **Rotates**: counts are compile-time constants per step.  Use
  the architecture's rotate instruction (`_rotl` / `_rotr` /
  Rust `u32::rotate_left` / `_mm_rolv_epi32` on AVX-512 etc.).

#### Verification

Apply SDS-BPT to one 4 KB chunk of `text_encrypted` -- the output
must equal the corresponding 4 KB of the post-pre-transform stream
that TEA actually reads at runtime, byte-exact.  Then run TEA-32
decrypt over the chunk; the result equals the runtime TEA output
byte-exact.

### SDS-PT (deprecated -- loader internal)

A separate per-chunk stream cipher (cumulative XOR + additive
keystream + feedback) lives at sd_base + 0x1d976 / 0x1d9a6.  It
processes sd_loader's own internal data (heap blob around
sd_base + 0x4f0a0) -- key schedule, integrity tables, or similar.
It is NOT on the bulk decrypt path.  Earlier analysis incorrectly
treated it as the bulk pre-transform.  Kept here only as a note
that this routine exists; it is not used by the offline decryptor.

### TEA-32

Standard Tiny Encryption Algorithm by Wheeler and Needham (1994).
Feistel network: 64-bit blocks, 128-bit key, 32 rounds.  Each round
mixes one of the two halves into the other via a fixed lane that
combines:

- a shift (`<<4` for one half, `>>5` for the other)
- an add (a 32-bit slice of the key)
- an XOR with the per-round constant `sum`, which evolves by
  adding (encrypt) or subtracting (decrypt) the magic delta
  0x9E3779B9 each round.  The delta is `floor(2^32 / phi)` --
  derived from the golden ratio -- and is the only constant in
  the cipher beyond the key.

Decrypt is a structural inverse of encrypt: same rounds, same key
schedule, but the `sum` counter starts at `delta * 32` and counts
down by `delta`, and the half-update is subtraction instead of
addition.

```c
void tea_decrypt(uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0x9E3779B9 * 32;
    for (int i = 0; i < 32; i++) {
        v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
        v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        sum -= 0x9E3779B9;
    }
    v[0] = v0; v[1] = v1;
}
```

Block size 64 bits => 8 input bytes -> 8 output bytes.  Each 4 KB
chunk is processed as 512 independent TEA blocks; **no mode chaining
at the TEA layer** -- all 512 blocks in a chunk are independent and
embarrassingly parallel.  (The chunk is the output of SDS-BPT, but
SDS-BPT also has no inter-dword chaining within a pass, so end-to-end
the per-dword path is independent.)

### SD-KDF (key derivation)

Trivial XOR-per-dword:

```c
void sd_kdf(const uint32_t key_post[4], uint32_t magic,
            uint32_t tea_key[4]) {
    for (int i = 0; i < 4; i++) tea_key[i] = key_post[i] ^ magic;
}
```

`magic = 0x89E0AD7D` for runblack.exe.  Self-inverse.

---

## Self-modifying code

`sd_loader` rewrites its own executable bytes in multiple unpacking
stages during process startup.  Most relevantly: the pre-transform
function body lives in a region that is REWRITTEN between the moment
the cleaner can first reliably dump sd_loader's memory and the
moment the bulk decrypt actually runs.

Concretely, the span `sd_base + 0x1d000..0x1e000` (4 KB containing
SDS-PT) differs by **~4013 out of 4096 bytes** between:

1. an early-startup memory dump of sd_loader (captured by the
   cleaner just after sd_loader has been mapped and relocated, but
   before BP3 releases), and
2. the same VA range read again at the moment of CipherWindowBegin
   inside the cipher window.

Static disassembly of the early dump for this region produces
nonsense; only a runtime snapshot (read while the target's CR3 is
active and CPL=3) yields valid instructions.  All offsets in this
document refer to the runtime form.

Smaller-scale self-modification likely exists elsewhere in
sd_loader but has not been exhaustively mapped.  For decryption
purposes only the pre-transform + TEA code regions matter, both
captured correctly via runtime snapshot.

---

## Missing pieces

### Important (blocks cross-binary usage)

**Magic universality.**  `0x89E0AD7D` is verified for one binary.
Whether it is universal across SafeDisc 2 releases, or per-binary,
is unknown.

**Handler byte universality.**  The SDS-BPT pass 0 and pass 1
handlers are 99-byte bytecode sequences embedded in sd_loader.text.
Whether their bytes are identical across SafeDisc 2 releases, or
generated per binary, is unknown.  Cross-validation against another
SD2 protected exe required.

**.rdata pass.**  Same SDS-BPT + TEA cipher very likely applies, but
not end-to-end verified.

### Nice-to-have

**PE rebuild port.**  Section table cleanup, import re-resolution,
indirect-call/jump-table fixups currently live in the Windows-only
cleaner; should be ported into the cross-platform `sd2decrypt`
sub-crate so offline decryption is a single self-contained tool.

[safedisc_tea_key.md]: safedisc_tea_key.md
