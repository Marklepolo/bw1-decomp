# dtk COFF split — object-filename collision on un-configured DLL modules (OS-independent)

**Reproduced on both** `dtk-windows 0.0.5` (`os error 183`, ERROR_ALREADY_EXISTS) **and**
`dtk-linux 0.0.5` (`os error 17`, File exists). So this is a dtk bug, **not** environment-specific.

## What happens
Splitting a DLL **module that has no `symbols.txt`** makes dtk auto-discover symbol names. Two
discovered C++ overloads sanitize to the **same** output `.o` filename, so the second write hits
create-new-on-existing and the split aborts:

```
 INFO Created 720 function splits
Failed: While processing 'LHaudiodllR.dll'
Caused by:
    File exists (os error 17)        # Linux;  Windows reports os error 183
```

Colliding object:
`build/.../obj/___qLHListenerUpdate_a..._a00_aZ.o`
(sanitized from `?LHListenerUpdate@LH_AudioSystem@@QAEXPAVLHAudioPoint@@0@Z`).

## Root cause (confirmed)
Of the four DLL modules, only two ship a config:

| module | config (`symbols.txt`) | split result |
|---|---|---|
| LHLog | **yes** | OK (defined names) |
| LHMultiplayer | **yes** | OK (defined names) |
| LHAudio | **no** | auto-discover → **collision** |
| LHDialog | **no** | auto-discover → (same risk) |

So the trigger is the **auto-discovery path** on the un-configured modules. dtk already
de-duplicates colliding symbol *names* (it logs `Duplicate fn name … renaming to fn_0x…`), but it
does **not** de-duplicate colliding sanitized *filenames*.

## Impact
- LHAudio (and LHDialog) cannot be split → cannot be built.
- `runblack-decrypted.exe` links against the rebuilt DLLs, so the **full linked build + the
  `build.sha1` verification cannot complete on any OS** until these modules build.
- Per-object objdiff verification of the main exe's own TUs is unaffected and works fine.

## Possible fixes (for discussion)
1. Ship `config/BW1E142/LHAudio/symbols.txt` (and `LHDialog/`) with defined names, like LHLog /
   LHMultiplayer already have — removes the auto-discovery collision.
2. dtk: when a sanitized object filename already exists, append a disambiguator (symbol address or a
   short hash) — mirror the existing duplicate-*name* handling.

## Related finding: the recorded LHLog hash matches no retail DLL
`config.yml` / `build.sha1` record `LHLogR.dll = 9ed6d153b24634b731ba062f38ee0fbb14001149`, but
that matches **none** of the retail `LHLogR.dll` across versions:

| version | LHLogR.dll sha1 |
|---|---|
| v1.00 | 5132ced04af35236529dbb722bebf11a8c8589ba |
| v1.10 | 34419383df8eafc4c4a755cb84da38e64b598f80 |
| v1.20 | 3c42f20350da2c54eb1ba0a61829b94d9883669a |
| v1.42 | 3c42f20350da2c54eb1ba0a61829b94d9883669a |

(LHAudio `35f149cb…` and LHDialog `64a22b88…` are identical across all four versions; LHMultiplayer
and LHLog vary.) So `9ed6d153…` appears to come from a **non-retail/patched build, or is incorrect** —
LHLog can't be split/verified against any retail DLL until this is reconciled. The other three
BW1E142 DLLs verify exactly.

## Environment
- `openblack/decomp-toolkit` v0.0.5 (both `dtk-windows-x86_64` and `dtk-linux-x86_64`)
- `bw1-dtk` @ `upstream/dtk-template` `d1782c8b`
