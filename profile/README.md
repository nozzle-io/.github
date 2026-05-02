# nozzle-io

Cross-platform GPU texture sharing between local processes.

## What is nozzle?

A C/C++17 static library for sharing GPU textures between applications on the same machine. An alternative to Syphon and Spout — with Linux support, modern C++ API, and bindings for Python, Rust, Swift, and more.

## Integration Status

| Integration | Module | macOS | Windows | Linux |
|---|---|---|---|---|
| [py.nozzle](https://github.com/nozzle-io/py.nozzle) | — | | | |
| [nozzle.rs](https://github.com/nozzle-io/nozzle.rs) | — | | | |
| [nozzle.swift](https://github.com/nozzle-io/nozzle.swift) | — | | N/A | N/A |
| [ofxNozzle](https://github.com/nozzle-io/ofxNozzle) | ofxNozzleSender | | | |
| [ofxNozzle](https://github.com/nozzle-io/ofxNozzle) | ofxNozzleReceiver | | | |
| [tcxNozzle](https://github.com/nozzle-io/tcxNozzle) | tcxNozzleSender | | | |
| [tcxNozzle](https://github.com/nozzle-io/tcxNozzle) | tcxNozzleReceiver | | | |
| [jit.nozzle](https://github.com/nozzle-io/jit.nozzle) | jit.nozzle.\* | ✅ | | N/A |
| [jit.nozzle](https://github.com/nozzle-io/jit.nozzle) | jit.gl.nozzle | | | N/A |
| [nozzle-TOP](https://github.com/nozzle-io/nozzle-TOP) | — | ✅ | | N/A |
| [obs-nozzle](https://github.com/nozzle-io/obs-nozzle) | — | | | |
| [blender-nozzle](https://github.com/nozzle-io/blender-nozzle) | — | | | |
| [nozzle-sokol](https://github.com/nozzle-io/nozzle-sokol) | — | | | |

## Platforms

macOS 12+ (Metal/IOSurface) · Windows 10+ (D3D11) · Linux (DMA-BUF)

## Documentation

[nozzle-io.org](https://nozzle-io.org)
