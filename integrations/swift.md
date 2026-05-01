---
layout: default
title: Swift (nozzle.swift)
---

[nozzle.swift](https://github.com/nozzle-io/nozzle.swift) provides an idiomatic Swift wrapper over the nozzle C ABI.

## Requirements

- macOS 12+
- Swift 5.9+
- Xcode 15+ (or Swift Toolchain)
- CMake 3.20+

## Setup

```bash
git clone git@github.com:nozzle-io/nozzle.swift.git
cd nozzle.swift
git submodule update --init --recursive
./Scripts/bootstrap.sh
```

## Build & Test

```bash
swift build
swift test
```

## Sender

```swift
import Nozzle

let sender = try Sender.create(name: "my-output", applicationName: "MyApp")

let frame = try sender.acquireWritableFrame(width: 1920, height: 1080, format: .rgba8Unorm)

let pixels = try frame.lockWritablePixels()
let buffer = pixels.data.bindMemory(to: UInt8.self, capacity: pixels.byteCount)
// ... write pixel data ...
pixels.unlock()

try sender.commitFrame(frame)
```

## Receiver

```swift
import Nozzle

let receiver = try Receiver.create(name: "my-output", applicationName: "MyViewer")

if receiver.isConnected, let info = receiver.connectedInfo {
    print("Connected to \(info.name): \(info.width)x\(info.height) @ \(info.estimatedFps) FPS")
}

let frame = try receiver.acquireFrame()
let info = frame.info
print("Frame \(info.frameIndex): \(info.width)x\(info.height)")

let pixels = try frame.lockPixels()
let buffer = pixels.data.bindMemory(to: UInt8.self, capacity: pixels.byteCount)
// ... read pixel data ...
pixels.unlock()
```

## Discovery

```swift
let senders = try Discovery.enumerateSenders()
for sender in senders {
    print("\(sender.name) (\(sender.applicationName)) — \(sender.backend)")
}
```

## Non-blocking Acquire

```swift
let frame = try receiver.acquireFrame(timeoutMs: 0)
```

## OpenGL Interop

```swift
// Publish an existing OpenGL texture
try sender.publishGLTexture(name: glTextureName, target: .texture2D,
    width: 1920, height: 1080, format: .bgra8Unorm)

// Copy a received frame to an OpenGL texture
try frame.copyToGLTexture(name: glTextureName, target: .texture2D,
    width: 1920, height: 1080, format: .bgra8Unorm)
```

## API Reference

### Sender

| Method | Description |
|--------|-------------|
| `Sender.create(name:applicationName:ringBufferSize:allowFormatFallback:)` | Create a sender |
| `sender.info` | Get sender metadata |
| `sender.acquireWritableFrame(width:height:format:)` | Acquire a frame for writing |
| `sender.commitFrame(_ frame:)` | Publish a committed frame |
| `sender.publishGLTexture(name:target:width:height:format:)` | Publish an OpenGL texture |

### Receiver

| Method | Description |
|--------|-------------|
| `Receiver.create(name:applicationName:receiveMode:)` | Create a receiver |
| `receiver.acquireFrame(timeoutMs:)` | Acquire the latest frame |
| `receiver.isConnected` | Check if connected to a sender |
| `receiver.connectedInfo` | Get connected sender details |

### Frame

| Method | Description |
|--------|-------------|
| `frame.info` | Get frame metadata |
| `frame.lockPixels()` | Map frame pixels for reading |
| `frame.lockWritablePixels()` | Map frame pixels for writing |
| `frame.release()` | Explicitly release (auto-released on deinit) |

### MappedPixels

| Property | Description |
|----------|-------------|
| `data` | Raw pointer to pixel buffer |
| `rowBytes` | Bytes per row |
| `width` / `height` | Dimensions |
| `format` | Pixel format |
| `byteCount` | Total buffer size |

## Memory Management

- `Sender`, `Receiver`, `Frame`, `Device` — reference types with `deinit` that call the corresponding C destroy functions
- `MappedPixels` — auto-unlocks on deinit; explicit `unlock()` available
- `Frame.release()` — safe to call multiple times (no-op after first release)

## Architecture

```
nozzle.swift
├── Sources/CNozzle/       C modulemap → deps/nozzle/include/nozzle/nozzle_c.h
├── Sources/Nozzle/        Swift wrapper over C ABI
├── deps/nozzle/           git submodule
└── Scripts/bootstrap.sh   Builds nozzle static library
```
