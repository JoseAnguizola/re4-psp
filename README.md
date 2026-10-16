# Resident Evil 4 PSP

A native port of Resident Evil 4 to the Sony PSP, built with the open-source
[pspdev](https://github.com/pspdev/pspdev) toolchain.

This repository contains engine code only. No game data is or will be stored
here; assets will be converted from a copy of the game you own.

## Building

Install pspdev and set `PSPDEV`, or use the `pspdev/pspdev` Docker image, then:

```sh
psp-cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
```

The output is `build/EBOOT.PBP`. Copy it to `PSP/GAME/RE4/` on a memory stick,
or open it in the [PPSSPP](https://www.ppsspp.org/) emulator.

Every push is built by GitHub Actions, and the EBOOT is attached to the run as
an artifact.
