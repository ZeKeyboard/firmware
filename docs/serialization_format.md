# General

- Everything is `uint16_t`

## Action

Action:
```
[N, key_1, modifier_1, media_1, ..., key_N, modifier_N, media_N]
```
where `N` is the sequence length.

## KeyMap

KeyMap:
```
[N, S, layer_1, row_1, col_1, Action_1, ..., layer_N, row_N, col_N, Action_N]
```
where N is the number of keys, and S is the total sum of every uint16 after this modulo 65500.
