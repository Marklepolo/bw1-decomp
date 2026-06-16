# MPFEConnectionStatus

`MPFEConnectionStatus` is the multiplayer front-end's record of which kind of online session the
player is in. Its single field `type` (a `LOBBY_TYPE`, offset 0x0) is set on the connection screen:
`LOBBY_TYPE_INTERNET` (0) for an online/GameSpy lobby, `LOBBY_TYPE_LAN` (1) for a LAN lobby, with
`_LOBBY_TYPE_COUNT` (2) used as the "not in a lobby" sentinel. The class exposes small predicates over
that field used throughout the MP UI flow.

## Functions

### `bool IsInternetLobby()`
Returns whether the front-end is currently in an internet (online) lobby — i.e. `type` is the zero
value `LOBBY_TYPE_INTERNET`. Compiles to the canonical `mov edx,[ecx]; xor eax,eax; test edx,edx;
sete al; ret` bool idiom.

| version | address |
|---|---|
| win 1.42 | `0x0062dac0` |
| win 1.10 | `0x00625130` |
| win 1.00 | `0x005e0c50` |
| mac | `MPFEConnectionStatus::IsInternetLobby()` |

The function body is byte-identical across 1.00/1.10/1.42 (and the sibling getters `IsLanLobby`
(`type == LOBBY_TYPE_LAN`) and the unnamed `IsInALobby` (`type != _LOBBY_TYPE_COUNT`) sit immediately
before/after it in every version), so the single translation unit matches all three.
