# Playstation 2© gsKit: primitives sample

Sample project for showing how drawing a colored primitives work.

## Technologies Used

* [ps2sdk](https://github.com/ps2dev/ps2sdk)
* [gsKit](https://github.com/ps2dev/gsKit)

## Requirements

1. Having installed and
   setup [ps2sdk](https://github.com/ps2dev/ps2sdk)/[ps2toolchain](https://github.com/ps2dev/ps2toolchain) or have the
   docker image of ps2sdk, which is available in their GitHub repo.
2. Change the `PS2DEV`, `PS2SDK`, `GSKIT`, `PS2EEBIN` variables in the [Makefile](Makefile).
3. When building ISO with more files than just the elf file, include them in the [SYSTEM.CNF](SYSTEM.CNF) file.
4. Change the include path in [main.c](main.c) of gsKit to the installed path. (For easiness, I've made a copy of
   gsKit's include in [external/gsKit/include](external/gsKit/include).)

## Example file structure

Local project:
```
- project
    ├─ include 
    │    └── *.h
    ├─ src 
    │    └── *.c
    ├─ main.c
    ├─ Makefile
    ├─ Makefile.pref
    ├─ Makefile.eeglobal
    └─ external
         └── (external libraries/headers)
```

SDK:
```
- ps2dev
    ├─ ps2sdk 
    ├─ gsKit
    └─ ee
       └─ bin
            └─ (compilers/tools)
```