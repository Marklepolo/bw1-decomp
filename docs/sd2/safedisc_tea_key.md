# SafeDisc 2 bulk-decrypt: TEA key + pipeline (SD 2.05 / 2.30)

Bulk `.text`/`.rdata` decrypt for the SDS-BPT + TEA-32 SafeDisc builds (2.05, 2.30.033). For
the polished cross-binary reference see `safedisc_overview.md`; for the AES-256 build (2.60.052)
see `SafeDisc_Cipher.md`.

## Pipeline

```
text_encrypted[chunk]  (4 KB on-disk ciphertext)
        |
        v  SDS-BPT pre-transform (2 passes, per-dword)
        |
        v  TEA-32 decrypt (key)   (8-byte blocks, 32 rounds)
        |
        v  text_plaintext[chunk]
```

Each 4 KB chunk is independent. SDS-BPT runs first as a per-dword 2-pass transform, then TEA-32
decrypts each 8-byte block of the result. The decrypt entry points live inside the SafeDisc
loader (`sd_base`-relative; `sd_base` is the per-run relocated VA of the loader).

## TEA-32 core

Function at `sd_base + 0x2FCA`. Standard 32-round TEA decrypt; signature
`tea_decrypt_block(buf_ptr, key_ptr)`.

```
v0 = LE u32 of buf[0..4]
v1 = LE u32 of buf[4..8]
sum = 0xC6EF3720                            (= 0x9E3779B9 * 32)
for _ in 0..32 {
    v1 -= ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3])
    v0 -= ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1])
    sum -= 0x9E3779B9
}
buf[0..4] = LE u32 v0
buf[4..8] = LE u32 v1
```

Delta + round count: `[sd_base + 0x35150] = 0x9E3779B9`, `[sd_base + 0x35154] = 32`.

### Verified TEA I/O (first 8 blocks, runblack.exe SD 2.05)

| call # | TEA input (pre-transformed) | TEA output (= text_plaintext) |
|---|---|---|
| 0 | `092ce6b61e0c049c` | `8b44240c538b5c24` |
| 1 | `97b961261c4ff36d` | `0c8bcb0fafc8568b` |
| 2 | `3de1137515192069` | `74240c03f1487814` |
| 3 | `fba4388780c09cf5` | `558b6c241c578d78` |
| 4 | `7756637a584880bc` | `012bf38bceffd54f` |
| 5 | `8b7a2efc0d2975ef` | `75f75f5d5e5bc210` |
| 6 | `98aaf8d20c596fce` | `0090909090909090` |
| 7 | `a5b4a3cce2853a7c` | `9090909090909090` |

The TEA outputs match the first 64 bytes of `text_decrypted.bin` byte-for-byte.

## Key derivation

The 16-byte TEA key materializes at a per-run target VA. SafeDisc derives it from `key_post`
(captured by the cleaner at `dw_bec`) by a single 32-bit XOR constant per LE u32:

```
TEA_key[i] = key_post[i] XOR 0x89E0AD7D     for i in 0..4
```

Verified (runblack.exe SD 2.05):
```
0xFB82B1CF ^ 0x89E0AD7D = 0x72621CB2   (b2 1c 62 72)
0x1BF734D3 ^ 0x89E0AD7D = 0x921799AE   (ae 99 17 92)
0x8B2AE05F ^ 0x89E0AD7D = 0x02CA4D22   (22 4d ca 02)
0x0A571CF7 ^ 0x89E0AD7D = 0x83B7B18A   (8a b1 b7 83)
```

The XOR delta `0x89E0AD7D` is a transient stack local of an obfuscated loader function; it is
not stored statically anywhere in target memory. Its provenance (per-binary constant,
SD2-wide constant, or computed) is unconfirmed — it is verified for runblack.exe (SD 2.05)
across independent runs, and treated as a per-version candidate.

### Captured keys

- SD 2.05 (runblack.exe): `b2 1c 62 72 ae 99 17 92 22 4d ca 02 8a b1 b7 83`
  (k0=0x72621CB2 k1=0x921799AE k2=0x02CA4D22 k3=0x83B7B18A). Mirrored in `docs/tea_key.bin`.
- SD 2.30.033 (BW110 runblack.exe): `40 62 80 63 c3 4b b1 d8 f5 3b 77 f8 31 ff 40 a0`. The
  SDS-BPT transform is unchanged from 2.05; only the key differs. See `SafeDisc_Cipher.md`.

## SDS-BPT pre-transform

A per-dword 2-pass transform applied to each 4 KB chunk before TEA. Dispatcher at
`sd_base + 0x1b69e`; `void(uint8_t *buf, size_t len)`.

```c
for (pass = 0; pass < 2; pass++) {
    out_ptr = buf;
    for (i = 0; i < len/4; i++) {
        work_val  = *out_ptr;
        work_val ^= broadcast(i);            // counter broadcast XOR
        work_val  = handler[pass](work_val); // CALL EBX, 99-byte handler
        *out_ptr  = work_val;
        out_ptr  += 4;
    }
}
```

Dispatch is `CALL EBX` at `sd_base + 0x1b9a5` into one of two 99-byte handlers (pass 0 at
`sd_base + 0x1b30e`, pass 1 at `sd_base + 0x1b371`). Each handler is a pure function of EAX
(no memory access), terminated by RET. Both passes are in-place on the same buffer.

### Counter broadcast (x86-faithful, NOT `i * 0x01010101`)

```c
uint32_t broadcast(uint32_t i) {
    return (i << 24) | (i << 16) | (i << 8) | i;  // each shift truncated to 32 bits before OR
}
```

For `i < 256` this equals `i * 0x01010101`. For `i >= 256` (reached every chunk, n_dwords=1024)
the high bits of `i` are lost in the shifts, so the multiplicative form is wrong. Reimplement
with the shift-OR form.

### Pass 0 handler (`sd_base + 0x1b30e`, 99 bytes)

```
NOP NOP
ROL EAX, 1
XOR EAX, 0x22cf7543
SUB EAX, 0x4c1a091b
SUB EAX, 0x3ecf00fc
XOR EAX, 0x4a745317
ROR EAX, 6
ADD EAX, 0x33992991
SUB EAX, 0x3b08421d
ROL EAX, 2
ROR EAX, 0                  ; ROR 0x80 -> no-op
XOR EAX, 0x28143e25
ROL EAX, 3
XOR EAX, 0x2c08711a
SUB EAX, 0x145a7207
ADD EAX, 0x22f12a73
XOR EAX, 0x76c36f07
ROL EAX, 28
ADD EAX, 0x563326d0
ROL EAX, 26
XOR EAX, 0x71427e58
XOR EAX, 0x7dd315d8
SUB EAX, 0x49ca69d6
RET
```

### Pass 1 handler (`sd_base + 0x1b371`, 99 bytes)

```
INC EAX
ADD EAX, 0x71531bf9
SUB EAX, 0x678d4ffa
ROR EAX, 6
ADD EAX, 0x1d715839
XOR EAX, 0x3ef04020
ADD EAX, 0x06c30f66
DEC EAX
INC EAX
ADD EAX, 0x10222baf
INC EAX
ROL EAX, 30
SUB EAX, 0x03b17bd3
XOR EAX, 0x719922cf
INC EAX
INC EAX
NEG EAX
ROL EAX, 12
ADD EAX, 0x3d183399
DEC EAX
ROR EAX, 22
NEG EAX
ROL EAX, 20
ROL EAX, 26
ROR EAX, 8
NEG EAX
INC EAX
INC EAX
ROR EAX, 20
ROL EAX, 19
ROL EAX, 25
DEC EAX
ROL EAX, 11
ROL EAX, 0                  ; ROL 0x80 -> no-op
DEC EAX
RET
```

Rotate counts are shown post-mask (x86 masks rotate counts to 5 bits for 32-bit operands).
NEG/INC/DEC are full-32-bit integer ops; the handlers have no conditional branches and only
the final EAX is observed, so flag side effects do not matter.

### Per-chunk algorithm

```c
void bulk_pretransform(uint32_t *buf, size_t n_dwords) {   // n_dwords = 1024 for 4 KB
    for (size_t i = 0; i < n_dwords; i++)
        buf[i] = pass0_handler(buf[i] ^ broadcast(i));
    for (size_t i = 0; i < n_dwords; i++)
        buf[i] = pass1_handler(buf[i] ^ broadcast(i));
}
```

Handler bytecode is static `.text` inside the loader (not generated at runtime); verified by
re-snapping the handler region at first dispatch. Verification: `text_encrypted[chunk]` →
`bulk_pretransform` (n_dwords=1024) → exact match to `tea_all_inputs[chunk]`, confirmed
4096/4096 bytes per chunk.

### Ground-truth triples (first 64 bytes, chunk 0)

```
input = .text[0:64]:
  d8800b6b 34051a3c c636a1e6 d71c8f8e  9f822036 a00dc9bf 7a292a11 27d71b2c
  db7459ea ca0a3261 dd3ca749 4f38ea04  08f1d567 ce0d4be7 cc847373 0a0403f3
after pass 0:
  f08e4834 9be68901 cf7b6b35 5df05dd9  af31ffa4 5680afbd 89b754cf ac8b3816
  7d313b32 d05506f1 5398e197 548d41d5  24d14745 1098272f 36d999b5 5650bbc2
after pass 1 (= TEA inputs):
  092ce6b6 1e0c049c 97b96126 1c4ff36d  3de11375 15192069 fba43887 80c09cf5
  7756637a 584880bc 8b7a2efc 0d2975ef  98aaf8d2 0c596fce a5b4a3cc e2853a7c
```

## SDS-PT (loader-internal, not on the bulk path)

A separate per-chunk stream cipher (cumulative XOR + additive keystream + feedback) at
`sd_base + 0x1d976 / 0x1d9a6` processes the loader's own internal data (heap blob around
`sd_base + 0x4f0a0`, key schedule / integrity tables). Its input is loader-internal memory,
not the encrypted `.text`, and its output does not feed TEA. It is not used by the offline
decryptor; it is noted here only to disambiguate it from SDS-BPT, with which it was initially
conflated.

Algorithm (for reference):
```c
void sds_pt(uint8_t *chunk, size_t len) {
    if (len > 0x1000) len = 0x1000;
    chunk[0] ^= 0x43;                       // sd_base+0x1d915
    uint8_t running_key = chunk[0] ^ 0x15;  // sd_base+0x1d942
    for (size_t i = 1; i < len; i++) {
        chunk[i] ^= chunk[i-1];             // chained XOR
        chunk[i]  = chunk[i] + running_key; // add running key
        running_key += chunk[i];            // feedback
    }
}
```

Verified in isolation (4096/4096) against a captured staging pair, but its `stage_pre` source
matches loader memory (`sd_dump.bin` offset 0x4f0d8), not `text_encrypted.bin`.

## secdrv (driver) involvement

Inside one full cipher window (180,152 ring transitions): 58,131 win32k.sys syscalls (GDI/USER
+ anti-tamper), 22,992 NT syscalls, and only 14 `NtDeviceIoControlFile` (syscall 0x6f) calls to
`\\.\secdrv`. 14 IOCTLs over the whole window means the kernel driver is an authorization
handshake only, not on the per-block path. Pre-transform + TEA both run user-mode.

## PANDA tooling

Cipher identification used PANDA record/replay (see `build/panda_plugin/`):

- `cipher_trace/` — TCG-only tracer: hypercalls, mode transitions, in-window memory writes,
  per-insn register sampling over a configurable PC range, and a guest-memory snapshot at first
  ring3 entry into a target VA range. The loader self-modifies, so the pre-transform code must be
  snapshotted during the cipher window (the live bytes differ from `sd_dump.bin` by ~4013/4096
  in the `sd_base+0x1d000..0x1e000` span); only the runtime snapshot disassembles correctly.
- `taint_stringops/` — propagates taint labels across `rep movs*`/`stos*`/`lods*`, which taint2's
  helper-call path misses.
- `scripts/dump_tea_key.py`, `dump_tea_io.py` — replay → hook the cipher fn → dump the 16-byte
  key / capture (input, output, key) per call.
- `analyze_eip_trace.py`, `verify_tea_decrypt.py` — hot-PC / crypto-constant analysis and TEA
  known-answer verification.

Build plugins with `pandare/pandadev` (has the source tree at `/panda`); replay with
`pandare/panda` (loads the prebuilt `.so`).

## Cleaner integration

`dump::find_and_dump_tea_key()` (in `src/dump.rs`) runs after `CipherWindowEnd`: it scans the
target heap in 4 KB strides for a 16-byte window equal to `key_post XOR <delta>` for each delta
in `CANDIDATE_DELTAS` (currently `0x89E0AD7D`). On a hit it writes `tea_key_live.bin` and emits
`Tag::TeaKeyCaptured`. To support another SD2 binary, capture its delta via a one-off PANDA
trace and add it to the candidate list.
