# nozzle-io

Cross-platform GPU texture sharing between local processes.

> This codebase is currently in its AI-slob prototyping phase: the code runs on momentum, vibes, and plausible intent.
> Proper debugging will be introduced once demand graduates from hypothetical to measurable.

## What is nozzle?

A C/C++17 static library for sharing GPU textures between applications on the same machine. An alternative to Syphon and Spout — with Linux support, modern C++ API, and bindings for Python, Rust, Swift, and more.

## Disclaimer / Notice

This library is currently a work in progress and contains many incomplete features and unverified implementations.
Although it may appear usable at first glance, it may not function correctly.

Please use it with the understanding that no guarantees are made regarding its behavior, and perform debugging, validation, and review as needed.
If you encounter problems, please do not become angry; instead, contributions in the form of Issues or Pull Requests would be greatly appreciated.

## Integration Status

*Last updated: 2026/05/31 20:37 (JST)*

| Integration | Module | macOS | Windows | Linux |
|---|---|---|---|---|
| [py.nozzle](https://github.com/nozzle-io/py.nozzle) | * | | | |
| [nozzle.rs](https://github.com/nozzle-io/nozzle.rs) | * | | | |
| [Nozzle.NET](https://github.com/nozzle-io/Nozzle.NET) | * | | | |
| [nozzle.swift](https://github.com/nozzle-io/nozzle.swift) | * | | N/A | N/A |
| [ofxNozzle](https://github.com/nozzle-io/ofxNozzle) | ofxNozzleSender | | | |
| [ofxNozzle](https://github.com/nozzle-io/ofxNozzle) | ofxNozzleReceiver | | | |
| [tcxNozzle](https://github.com/nozzle-io/tcxNozzle) | tcxNozzleSender | | | |
| [tcxNozzle](https://github.com/nozzle-io/tcxNozzle) | tcxNozzleReceiver | | | |
| [jit.nozzle](https://github.com/nozzle-io/jit.nozzle) | jit.nozzle.* | ✅ | | N/A |
| [jit.nozzle](https://github.com/nozzle-io/jit.nozzle) | jit.gl.nozzle.* | | | N/A |
| [nozzle-TOP](https://github.com/nozzle-io/nozzle-TOP) | * | ✅ | | N/A |
| [obs-nozzle](https://github.com/nozzle-io/obs-nozzle) | * | | | |
| [blender-nozzle](https://github.com/nozzle-io/blender-nozzle) | * | | | |
| [nozzle-sokol](https://github.com/nozzle-io/nozzle-sokol) | * | | | |
| [nozzle.unity](https://github.com/nozzle-io/nozzle.unity) | * | | | |
| [nozzle-viewer](https://github.com/nozzle-io/nozzle-viewer) | * | 🟦 | 🟦 | 🟦 |
| [nozzle-ffgl](https://github.com/nozzle-io/nozzle-ffgl) | NozzleReceive | 🟦 | 🟦 | N/A |
| [nozzle-ffgl](https://github.com/nozzle-io/nozzle-ffgl) | NozzleSend | 🟦 | 🟦 | N/A |

## Platforms

macOS 12+ (Metal/IOSurface) · Windows 10+ (D3D11) · Linux (DMA-BUF)

## Documentation

[nozzle-io.org](https://nozzle-io.org)
