# Building the Virtus Scale firmware

Target board: **Adafruit Feather nRF52840 Sense**, SoftDevice **S140 v6**
(Adafruit nRF52 core 1.7.0).

## ⚠️ Required build flag (v1.7.2+)

The auth handshake bundles **micro-ecc** for ECDSA P-256 signing. On the
Cortex‑M4 the library auto-selects an ARM-assembly path that pulls in
`asm_arm.inc`, which is **not** included here. You **must** force the portable
C path with `-DuECC_PLATFORM=0`, or the build fails with
`fatal error: asm_arm.inc: No such file or directory`.

## Compile

```bash
arduino-cli compile \
  --fqbn adafruit:nrf52:feather52840sense:softdevice=s140v6 \
  --build-property "compiler.c.extra_flags=-DuECC_PLATFORM=0" \
  --build-property "compiler.cpp.extra_flags=-DuECC_PLATFORM=0" \
  --export-binaries \
  virtus_scale
```

(In the Arduino IDE, add `-DuECC_PLATFORM=0` via a `build.extra_flags` entry,
or a `platform.local.txt`.)

## Package the signed DFU zip

```bash
nrfutil pkg generate \
  --hw-version 52 --sd-req 0xB6 \
  --application-version <int> \
  --application <build>/virtus_scale.ino.hex \
  --key-file ../dfu_keys/virtus_private.pem \
  virtus_scale_vX.Y.Z_dfu.zip
```

## Notes / gotchas

- **micro-ecc `.inc` files were renamed to `.h`** (`uECC_platform.h`,
  `uECC_curve.h`) because the Arduino build doesn't copy `.inc` files to its
  build dir. The `#include`s in `uECC.c` were updated to match.
- The nRF5-SDK default RNG branch in `uECC_platform.h` is disabled — the sketch
  supplies its own RNG via `uECC_set_rng()` (SoftDevice hardware RNG).
- Signing keys: firmware is signed for DFU with `dfu_keys/virtus_private.pem`;
  the **scale-auth** device key lives in `auth_keys/` (private key compiled into
  the firmware, public key embedded in the app). Keep both private keys secret.
