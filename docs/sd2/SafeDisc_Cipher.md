# Black & White — SafeDisc protection analysis (runblack.exe)

Analysis of the SafeDisc copy protection on `runblack.exe`, on a Windows 11 host
with no `secdrv.sys`. Two game versions were studied; each ships a different
SafeDisc build with a different `.text` cipher.

| Game | SafeDisc | `.text` cipher | Status |
|------|----------|----------------|--------|
| v1.10 (`BW110/BW/runblack.exe`) | 2.30.033 | SDS-BPT + TEA-32 | Key recovered; offline-decryptable |
| v1.20 (`BW120/runblack.exe`)    | 2.60.052 | SDS-BPT + AES-256 | Architecture, keys, and OEP recovered; exact keystream combine not reproduced offline |

Version is read from the `BoG_ *90.0&!!  Yy>` signature at file offset `0xfd4`; the
three LE u32 at sig+0x20 are major/minor/build.

---

## 1. Bypassing the protection (both versions)

SafeDisc requires `secdrv.sys` (kernel driver) + the media (CD) check, and runs
anti-debug/anti-tamper. On Win10/11 `secdrv` is absent. The replacement used is
**SafeDiscShim** (RibShark): a user-mode `drvmgt.dll` delivered via an AppCompat SDB
that emulates the secdrv IOCTLs and neutralises the anti-debug, installed after the
loader's checks.

Constraints:
- The shim applies only to Explorer/shell launches, not to a process the cleaner
  spawns itself (a cleaner-spawned child shows the secdrv "admin" dialog).
- The CD must be in the drive — SafeDisc's media check is separate from secdrv and
  gates the bulk decrypt. Without it, `.text` stays encrypted in memory.
- Running the game free crashes the host (old D3D on Win11), so the decrypted image
  must be captured under suspension, before the game's entry point runs.

## 2. Capturing the decrypted code — crash-safe OEP dump

Implemented in `src/inject.rs::oep_dump` (env `SD2_OEP_DUMP`):

1. Scan-only: the user double-clicks `runblack.exe`; the cleaner watches for the
   process (it relaunches itself, so there are 2 PIDs) and `NtSuspendProcess` each
   instance the instant it appears, freezing it before it can crash.
2. Step under suspension (`NtResumeProcess`/`NtSuspendProcess` bursts: 30 ms through
   the loader, 3 ms near the end) until `.text` is fully decrypted (probe the end of
   the section), still before the OEP.
3. Snapshot decrypted `.text`/`.rdata` → `SD2cleaned.exe` + `text_decrypted.bin`.
4. `TerminateProcess` everything.

This yields the fully decrypted game code for both versions; load `SD2cleaned.exe` in
IDA/Ghidra to read the game code. It is not a runnable no-CD exe (the loader stub, OEP,
and imports are untouched). v1.20 OEP = `0x7ca49f` (from the loader entry's `jmp`).

## 3. v1.10 (SafeDisc 2.30.033)

Cipher per 4 KB chunk: SDS-BPT (per-dword: counter-XOR, `pass0`, counter-XOR, `pass1`;
counter = `(i<<24)|(i<<16)|(i<<8)|i`) then TEA-32 (8-byte blocks, 32 rounds, δ=0x9E3779B9).

The TEA key cannot be derived from plaintext, so it is read from the loader's heap: dump
the suspended loader's memory (`SD2_DUMP_MEM` → `keymem.bin`), then brute-search every
16-byte window `K` for `TEA_decrypt(SDS-BPT(enc_block0), K) == dec_block0`.

TEA key = `40 62 80 63 c3 4b b1 d8 f5 3b 77 f8 31 ff 40 a0` (heap VA ~0x4fdffa0).
Offline `SDS-BPT + TEA(key)` reproduces the runtime dump 100%. Wired into
`tools/sd2decrypt` (`sd2decrypt <in> <out>`) for a no-run offline decrypt.

The SDS-BPT `pass0`/`pass1` constants are identical to the older 2.05 build; only the
TEA key changed. The repo's hardcoded `b2 1c 62 72…` is the 2.05 key, not this one.

## 4. v1.20 (SafeDisc 2.60.052)

2.60 keeps the same SDS-BPT (`pass0`/`pass1` disassembled byte-for-byte identical:
`rol1; xor 0x22cf7543; … xor 0x76c36f07; … sub 0x49ca69d6`; passes 0x63 bytes apart)
but replaces TEA with AES-256:

- AES T-table round in the loader: 4× 256-entry tables (`Te0[0]=0xc66363a5`, Te1/2/3 at
  +0x400/+0x800/+0xc00), byte-extract + XOR + round keys, `cmp ecx,3` rounds loop.
- AES block-encrypt fn at `0x4a8ac50`: ESP-frame, `input[i] ^ roundkey[i]` then Te rounds;
  round keys at `0x4b339d8+`.
- A self-consistent AES-256 key candidate in the decrypt arena:
  `1d19914e 40e47a98 2c023f61 deba0a12 11ca6be9 c4f32ce4 c83406d8 dbad0ab0` (full
  60-word FIPS-197 expansion matched memory). A second, run-varying schedule sits in the
  live context at `0x4b339d8`. See `SafeDisc_Offline_Decryption_Analysis.md`: a later
  scan over both dumps found 0 self-consistent static keys, so neither is a usable static
  `.text` key.

### Decryption pipeline (mapped via `_src/deob.py`)

```
media check (disc ok → status 0xfa)
  → LCG config decrypt    : a 198-byte config blob decrypted byte-wise by an LCG
                            (keystream = state&0xff; state *= mult [0x4b339c4]; out = ks XOR in)
  → AES-256 key derivation: 0x4a8c95a/0x4a8cf37 AES-process 0x20/0x18-byte key material
                            (the .text master key is computed at runtime from the config)
  → SDS-BPT               : the 2.05/2.30 pass0/pass1 keystream generator
  → combine               : XOR a generated keystream into .text
```

The combine is XOR with a keystream, and the keystream (`enc XOR dec`) is available from
the dump. What is not reproduced offline is the keystream generation chain
(config → AES-derived key → SDS-BPT → keystream). The master key feeding it is derived at
runtime, which is why no fixed key + standard mode reproduces `enc → dec`.

Confirmed primitives in the loader:
- LCG byte cipher (`out=ks^in; ks=state&0xff; state*=mult`) — config blobs.
- AES-256 block encrypt (T-tables, round keys @`0x4b339d8`) — key derivation.
- SDS-BPT pass0/pass1 (identical to 2.05/2.30) — keystream generation.

### Full `.text` cipher

Recovered from the captured stack of the live AES round (return addresses → call chain)
and traced with `_src/deob.py`.

Driver `0x4a73bcd` decrypts `.text` in 0x1000 (4 KB) pages:
```
per page:  read encrypted page → 0x4a8f9f0   into a 0x1000 stack buffer
           cipher(buf, len, callback=0x4b0374e) = 0x4a8cf40   [cipher, in place]
           write(ctx=[0x4b33820], dst, len, buf) = 0x4a8fbe0
```

Cipher `0x4a8cf40` — a byte-wise AES-CFB stream cipher. Per output byte:
```
[0x4b339d0]++                                   ; global byte counter
stage1: memops(key material [0x4b33ae8], 0x20)  ; 0x4ac7720 / 0x4ac7390
        0x4a8caf0(buf,0x20)  -> loads 8 dwords as AES round keys @0x4b339d8
        0x4a8ac50(reg=[0x4b33ad8], rk, out)      ; AES round over the 16-byte CFB register
stage2: ... 0x18-byte ... 0x4a8bd10(...)         ; second AES variant
stage3: ... 0x10-byte ... 0x4a8c520(...)         ; third AES variant
0x4ad0870(...,3)                                 ; mix
ks = callback 0x4b0374e(result,4)[0]             ; LCG over the 4-byte result -> 1 keystream byte
out = (*buf) XOR ks                              ; combine
*buf = out ; [0x4b33ad8] = out                   ; CFB feedback (plaintext into AES register)
buf++
```

Primitives (all confirmed in the loader):
- `0x4a8caf0` load-round-keys (buf → `0x4b339d8..`).
- `0x4a8ac50`/`0x4a8bd10`/`0x4a8c520` three AES-round variants (Te-tables + round keys).
- `0x4b0374e` LCG byte transform (`out=(state&0xff)^in; state*=mult [0x4b339c4]`).
- combine = XOR (`xor dl,cl` @ `0x4a8d0a0`).
- feedback = CFB (decrypted byte shifts into `[0x4b33ad8]`), so the keystream has no
  period and no static key/mode reproduces it.
- phase params `[0x4b071d0..e0] = {10,4,4,50000,150000}` — counter thresholds
  (`cmp [0x4b339d0],0xc350/0x249f0`); keystream construction changes after byte 50000/150000.

CFB feedback verified against the live process: at the mid-bulk capture, counter
`[0x4b339d0]` = 2182016 (44.7%), and the live AES register `[0x4b33ad8]` first dword =
`fe d9 2f e8` = the last 4 decrypted bytes `dec[ctr-4..ctr]` = `e8 2f d9 fe` byte-reversed.
The register holds the most-recent decrypted dword.

### Offline regenerator status

A byte-exact offline reimplementation is specified but not built. The per-byte round keys
are produced by a C++ object at `[0x4b347b0]` via virtual dispatch
(`vt=[obj]; call [vt+0x10] -> obj2; call [[obj2]+4]`) — an RNG/key-schedule class
hierarchy whose data resolves to the AES T-tables wrapped in C++ objects
(`[obj+0xc]` → array of 16-byte records `{vtable 0x4b08878, table_ptr=0x4ce2ea8+n*0x408,
size=0x400, 0x10}`). Everything is wrapped in anti-disassembly: junk
`call <addr-that-is-just-ret>` thunks (push/pop-balanced no-ops), per-basic-block `jmp`
mazes, and ESP-frames.

A byte-exact regenerator therefore requires reimplementing the 3 AES variants, `0x4a8caf0`,
the LCG `0x4b0374e`, the memops `0x4ac7720`/`0x4ac7390`, and the C++ RNG class (vtables +
concrete virtual methods + per-object state), plus a clean byte-boundary initial state (AES
register IV + key material `[0x4b33ae8]` + round-key seed from the LCG-config + AES
key-derivation stages). It reproduces output already obtainable by dumping the running game
(`SD2cleaned.exe`), so it was not pursued. The structure is fully specified; entry points
above are the starting point.

## 5. Reusable tooling

- `oep_dump` (inject.rs): suspend-on-find, step-to-decryption, mid-bulk snapshot
  (`SD2_DUMP_MEM_EARLY`, fine-step to land mid-decrypt), page-by-page low-256MB dump,
  `log_thread_eips` (full CONTEXT; the non-ntdll thread's EIP pinpoints the live cipher;
  dumps its EIP/ESP/EBX regions).
- `_src/deob.py` — recursive-descent de-obfuscating disassembler: follows real control flow,
  drops the junk-`jmp` maze + filler. Required for reading SafeDisc 2.60 code.
- Key recovery from a dump: scan for a 16/24/32-byte window whose FIPS-197 expansion is
  self-consistent (AES key); for TEA, a known-plaintext window scan.
- Reverting the host: `sdbinst -u SafeDiscShim.sdb` + delete `drvmgt.dll` from System32 and
  SysWOW64. (A 32-bit `drvmgt.dll` must live in SysWOW64.)

## 6. No-CD rebuild (v1.20)

`runblack_nocd.exe` is a clean unpacked, no-CD, no-SafeDisc executable that reaches the
original game entry point. Pipeline:

1. OEP-trap dump (`SD2_UNPACK`, inject.rs): trap `EB FE` at OEP `0x7ca49f` after the loader
   resolves imports, dump the fully-loaded image (`dumpimg.bin`) + `modules.txt`.
2. Import tracer (`_src/imptrace.py`, Unicorn): emulate each SafeDisc import-redirection stub
   through the resolver offline (GDT/FS+TEB for the resolver's SEH; reset resolver globals per
   stub), capturing the import at the `GetProcAddress(hMod,name)` call or the fast-path
   trampoline. 183/184 stubs resolved (1 deep anti-dump VirtualProtect-loop stub
   placeholdered). The real game IAT (`0x8a9000`, 596 imports) has 184 stubs + 413 direct.
3. Rebuild (`_src/rebuild_nocd.py`): resolve the full IAT, group by the IAT's
   null-terminated per-DLL runs, build a fresh `.import` section whose FirstThunks point at
   the game IAT, set EP = OEP rva `0x3ca49f`, make the IAT section writable, zero the checksum
   → `runblack_nocd.exe` (22 DLLs, 596 imports).

Two reconstruction bugs found and fixed via loader-snap diagnosis (`_src/debugload.py`):
1. kernel32→ntdll forwarders: the fast path captured the ntdll target (`RtlAllocateHeap`)
   instead of the kernel32 export the game imports (`HeapAlloc`); mapped back.
2. name truncation at 80 chars cut long C++-mangled exports
   (`?CheckSavedPacketsAvail@LHMPPacketSave@@…`) → loader `STATUS_ENTRYPOINT_NOT_FOUND`;
   raised to 400.

Validation: debug-launch to the OEP breakpoint (debugger hidden via 32-bit WoW64 PEB; loader
snaps on) reaches OEP `0x7ca49f` with 75 DLLs loaded and all imports resolved, SafeDisc loader
bypassed. Running past the OEP runs the game itself (same old-D3D-on-Win11 issue, unrelated to
the unpack).
