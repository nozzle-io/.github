---
layout: default
title: Python (py.nozzle)
---

[py.nozzle](https://github.com/nozzle-io/py.nozzle) provides Python bindings for nozzle via [nanobind](https://github.com/wjakob/nanobind). Receive pixels as NumPy copies or read-only raw mapped views.

## Install

```bash
pip install nozzle
```

### From Source

```bash
git clone --recurse-submodules https://github.com/nozzle-io/py.nozzle.git
cd py.nozzle
pip install .
```

## Requirements

- Python 3.9+
- CMake 3.20+
- C++17 compiler
- macOS 12+ / Windows 10+ / Linux (glibc 2.31+)

## Sender

```python
import nozzle
import numpy as np

sender = nozzle.Sender.create("my_output", "MyApp")

img = np.zeros((480, 640, 4), dtype=np.uint8)
img[100, 100] = [255, 128, 64, 255]
sender.publish_array(img)
```

## Receiver

```python
import nozzle

receiver = nozzle.Receiver.create("my_output", "MyViewer")

frame = receiver.acquire_frame(timeout_ms=1000)
if frame.valid():
    info = frame.info()
    print(f"{info.width}x{info.height}, format={info.format}")

    arr = frame.get_array()
    print(arr.shape, arr.dtype)
```

## Discovery

```python
senders = nozzle.enumerate_senders()
for s in senders:
    print(f"{s.name} ({s.application_name}) — {s.backend}")

names = nozzle.list_senders()
```

## NumPy Pixel Access

`frame.get_array()` returns a packed, top-left-origin copy in logical channel
order (BGRA8 is converted to RGBA). RGBA16 Float is widened to float32.
For raw storage without that normalization copy:

```python
frame = receiver.acquire_frame(timeout_ms=1000)
if frame.valid():
    locked = frame.lock_pixels()
    raw = locked.to_ndarray()
    print(locked.format, raw.shape, raw.strides)
```

The raw view is read-only, retains its mapping owner and uses the actual storage
channel order and row stride. BGRA8 remains BGRA; half-float data is exposed as
uint16 bit patterns. Backend mapping can still require staging/readback.
Read-only does not freeze producer updates; use a copy for retained data.

`Frame` and `LockedPixels` do not implement DLPack. The non-conforming
`__dlpack__` / `__dlpack_device__` methods were removed; migrate direct calls to
`get_array()` or `to_ndarray()` instead. The former direct Frame method kept
RGBA16 Float as uint16 bits, unlike `get_array()` widening. PyTorch/JAX DLPack
interoperability is not provided. See the [current binding documentation](https://github.com/nozzle-io/py.nozzle#numpy-api-migration).

## Pixel Format Mapping

NumPy dtypes map automatically to nozzle formats:

| NumPy dtype | Channels | Nozzle Format |
|-------------|----------|---------------|
| `uint8` | 1 | R8 UNORM |
| `uint8` | 2 | RG8 UNORM |
| `uint8` | 4 | RGBA8 UNORM |
| `float32` | 1 | R32 Float |
| `float32` | 4 | RGBA32 Float |
| `float16` | 4 | RGBA16 Float |

## API Reference

### Sender

| Method | Description |
|--------|-------------|
| `Sender.create(name, application_name, ring_buffer_size=3)` | Create a sender |
| `sender.publish_array(array)` | Publish a NumPy array as a frame |
| `sender.info()` | Get sender metadata |
| `sender.valid()` | Check if sender is initialized |

### Receiver

| Method | Description |
|--------|-------------|
| `Receiver.create(name, application_name)` | Create a receiver |
| `receiver.acquire_frame(timeout_ms=0)` | Acquire latest frame |
| `receiver.valid()` | Check if receiver is initialized |

### Frame

| Method | Description |
|--------|-------------|
| `frame.info()` | Get frame metadata (width, height, format, frame_index) |
| `frame.get_array()` | Copy frame data to NumPy array |
| `frame.lock_pixels()` | Transfer frame ownership to `LockedPixels` for read-only raw mapped access |
| `frame.valid()` | Check if frame holds valid data |
| `frame.release()` | Explicitly release frame |

## Architecture

The Python extension wraps the nozzle C ABI via nanobind. No C++ API usage:

```
py.nozzle
├── src/nozzle.cpp     nanobind C++ extension
├── src/nozzle/        Python package (__init__.py)
├── libs/nozzle/       git submodule
└── tests/             pytest suite
```
