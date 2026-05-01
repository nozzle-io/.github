---
layout: default
title: Architecture
---

Nozzle is organized into four layers, from platform infrastructure up to integration wrappers.

## Layer Diagram

```
Layer 4: Integration Wrappers
        py.nozzle, nozzle.rs, nozzle.swift, ofxNozzle,
        jit.nozzle, nozzle-TOP, obs-nozzle, blender-nozzle,
        nozzle-sokol, tcxNozzle

Layer 3: OpenGL Interop
        Copy-based GL↔backend texture transfer
        macOS: GL → IOSurface (GPU blit)
        Windows: GL → staging → D3D11 (CPU copy)
        Linux: GL → DMA-BUF mmap (CPU copy)

Layer 2: Backend-Native API
        Metal/IOSurface (macOS)
        D3D11 shared textures (Windows)
        DMA-BUF/GBM/EGL (Linux)

Layer 1: Common API
        sender, receiver, frame, texture, device, discovery
        Result<T> error handling, thread-safe objects

Layer 0: Platform Infrastructure
        IPC (POSIX shm / Windows CreateFileMapping)
        Registry (named sender/receiver lookup)
        Ring buffer synchronization (atomic counters)
        Shared memory layout
```

## Core Concepts

### Named Sender/Receiver Model

Senders and receivers are identified by name. A receiver connects to a sender by matching its name. Discovery (`enumerate_senders()`) lists all active senders on the local machine.

### Ring Buffer

Each sender maintains a ring buffer of shared textures (configurable size, default 3). This decouples sender and receiver frame rates. The sender writes to the next available slot; the receiver reads the latest completed slot.

### Shared State

Sender and receiver communicate through platform-specific shared memory:

- **macOS/Windows**: POSIX `shm_open` / Windows `CreateFileMappingA`
- **Linux**: POSIX `shm_open`

The shared state contains ring buffer metadata: frame indices, timestamps, sender info, and format descriptors.

### Synchronization

| Platform | Mechanism |
|----------|-----------|
| macOS | IOSurface lock (`IOSurfaceLock`/`IOSurfaceUnlock`) |
| Windows | Keyed mutex (`IDXGIKeyedMutex`) |
| Linux | Atomic counters in shared memory |

### Crash Cleanup

Nozzle uses lazy detection. If a sender crashes, the receiver detects the dead sender on the next access failure (timeout or invalid shared state). No explicit cleanup protocol is needed.

## Transfer Modes

| Mode | Description |
|------|-------------|
| `zero_copy_shared_texture` | GPU memory shared directly between processes |
| `gpu_copy` | GPU-side blit between incompatible surfaces |
| `cpu_copy` | Readback to CPU, upload to GPU (slowest) |

Backend-native sharing uses zero-copy. OpenGL interop on Windows uses CPU copy. GL interop on macOS uses GPU copy via IOSurface.

## Error Handling

`Result<T>` pattern with explicit error checking:

```cpp
auto result = nozzle::sender::create(desc);
if (!result.ok()) {
    // result.error().code    -> ErrorCode
    // result.error().message -> std::string
}
auto sender = std::move(result).value();
```

No exceptions, no `std::optional` error info. Every fallible operation returns `Result<T>`.

## Thread Safety

Sender and receiver objects are individually thread-safe. The same `sender` can be called from multiple threads simultaneously. The same `receiver` can poll for frames from multiple threads.

## Repository Layout

```
include/nozzle/              Public C++ headers
include/nozzle/backends/     Backend-specific headers
  metal.hpp                    Metal/IOSurface
  d3d11.hpp                    D3D11
  opengl.hpp                   GL interop
  linux.hpp                    DMA-BUF
src/common/                   Shared implementation
src/c_api/                    C ABI wrapper
src/backends/
  metal/                       .mm files (ObjC++)
  d3d11/                       .cpp files
  opengl/                      .cpp files
  linux/                       .cpp files
libs/plog/                    Header-only logging (submodule)
tests/                        Unit + integration tests
examples/                     Minimal examples
```
