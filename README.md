# PS4HEN Lite 2.2.0

A lightweight version of PS4HEN that only includes the essential features.

This project is based on [Scene-Collective](https://github.com/Scene-Collective)/**[ps4-hen](https://github.com/Scene-Collective/ps4-hen)** and [Scene-Collective](https://github.com/Scene-Collective)/**[ps4-payload-sdk](https://github.com/Scene-Collective/ps4-payload-sdk)**.

The goal was to build a HEN similar to GoldHEN Lite.  
So there are no configuration options, servers, in-game cheats and patches, or plugin support.

## Features

- Homebrew Enabler
- Jailbreak
- Sandbox Escape
- Debug Settings
- VR Support
- Remote Package Install
- Rest Mode Support
- External HDD Support
- Bypass Firmware Checks
- Debug Trophies Support
- sys_dynlib_dlsym Patch
- Never Disable Screenshot
- Remote Play Enabler
- Firmware Update Block
- Disable ASLR

## Building

Clone the repository:

```sh
git clone https://github.com/KrisztianKende/PS4HEN_Lite.git
```

Optionally apply a patch to change the supported firmware range:

```sh
7z e -so 900-1300.diff.7z | patch -p1
```

Compile the payload:

```sh
./build.sh
```

## Credits

Massive thanks to all the original contributors:
- [qwertyoruiopz](https://x.com/qwertyoruiopz)
- [Specter](https://x.com/SpecterDev)
- [flat_z](https://x.com/flat_z)
- [CTurt](https://github.com/CTurt)
- [idc](https://x.com/3226_2143)
- [Joonie](https://github.com/Joonie86/)
- [Vortex](https://github.com/xvortex)
- [stooged](https://github.com/stooged)
- [zecoxao](https://x.com/notnotzecoxao)
- [SiSTRo](https://github.com/SiSTR0)
- [SocraticBliss](https://x.com/SocraticBliss)
- [ChendoChap](https://github.com/ChendoChap)
- [Biorn1950](https://github.com/Biorn1950)
- [Al-Azif](https://github.com/Al-Azif)
- [BestPig](https://x.com/BestPig)
- [LM](https://x.com/LightningMods)
- [Echo Stretch](https://x.com/stretchecho)
- [illusiony](https://github.com/illusion0001)
- Anonymous
