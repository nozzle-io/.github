---
layout: default
title: Metal / IOSurface Backend
---

The macOS backend uses **Metal** for GPU rendering and **IOSurface** for cross-process texture sharing.

## Overview

Textures are backed by `IOSurface` objects, which are kernel-managed shared memory buffers that can be used by both Metal and OpenGL. The sender creates IOSurface-backed Metal textures in a ring buffer. The receiver looks up the IOSurface by ID and creates its own Metal texture view.

## How It Works

```
Sender Process                              Receiver Process
─────────────────                          ─────────────────
Metal Device                               Metal Device
    │                                           │
    ├── Create IOSurface                         │
    ├── Wrap as MTLTexture                       │
    ├── Render into texture                      │
    ├── Publish IOSurface ID                     │
    │      via shared state                      │
    │                                           ├── Read IOSurface ID
    │                                           ├── Create MTLTexture view
    │                                           ├── Read texture
    │                                           │
    └── Ring buffer (N surfaces)                 └── Frame acquisition
```

## Thread Safety

IOSurface locking (`IOSurfaceLock`/`IOSurfaceUnlock`) provides synchronization between processes. The sender locks before writing, unlocks after. The receiver locks before reading.

## Zero-Copy

Texture data is never copied between processes. Both sides read/write the same IOSurface-backed memory. Transfer mode is `zero_copy_shared_texture`.

## Backend API

```cpp
#include <nozzle/backends/metal.hpp>

namespace nozzle::metal {

Result<device> wrap_device(const device_desc &desc);
Result<texture> wrap_texture(const texture_wrap_desc &desc);
mtl_texture_handle get_texture(const texture &tex);
surface_handle get_io_surface(const texture &tex);

}
```

### Types

```cpp
using mtl_device_handle = void *;       // id<MTLDevice>
using mtl_texture_handle = void *;      // id<MTLTexture>
using surface_handle = void *;          // IOSurfaceRef
using pixel_format_value = uint32_t;    // MTLPixelFormat
using surface_id = uint32_t;            // IOSurfaceID
```

### device_desc

```cpp
struct device_desc {
    mtl_device_handle device{nullptr};
};
```

### texture_wrap_desc

```cpp
struct texture_wrap_desc {
    mtl_texture_handle texture{nullptr};
    surface_handle io_surface{nullptr};
    pixel_format_value format{0};
    uint32_t width{0};
    uint32_t height{0};
};
```

### wrap_device

Wrap an existing Metal device for use with nozzle.

```cpp
Result<device> wrap_device(const device_desc &desc);
```

```cpp
auto dev = nozzle::metal::wrap_device({
    .device = mtl_device  // id<MTLDevice>
}).value();
```

### wrap_texture

Wrap an existing IOSurface-backed Metal texture.

```cpp
Result<texture> wrap_texture(const texture_wrap_desc &desc);
```

### get_texture / get_io_surface

Extract native handles from a nozzle texture.

```cpp
mtl_texture_handle get_texture(const texture &tex);
surface_handle get_io_surface(const texture &tex);
```

## OpenGL Interop

macOS GL interop uses `CGLTexImageIOSurface2D` for GPU-side blit between GL textures and IOSurface:

```cpp
#include <nozzle/backends/opengl.hpp>

nozzle::gl::gl_texture_desc gl_desc{
    .name = gl_texture_name,
    .target = GL_TEXTURE_2D,
    .width = 1920,
    .height = 1080,
    .format = nozzle::texture_format::bgra8_unorm
};

// Publish GL texture to nozzle sender
nozzle::gl::publish_gl_texture(sender, gl_desc);

// Copy received frame to GL texture
auto frame = receiver.acquire_frame({.timeout_ms = 1000}).value();
nozzle::gl::copy_frame_to_gl_texture(frame, gl_desc);
```

## Format Mapping

| Nozzle Format | MTLPixelFormat |
|---------------|----------------|
| `r8_unorm` | `MTLPixelFormatR8Unorm` |
| `rg8_unorm` | `MTLPixelFormatRG8Unorm` |
| `rgba8_unorm` | `MTLPixelFormatRGBA8Unorm` |
| `bgra8_unorm` | `MTLPixelFormatBGRA8Unorm` |
| `rgba8_srgb` | `MTLPixelFormatRGBA8Unorm_sRGB` |
| `r16_float` | `MTLPixelFormatR16Float` |
| `rgba16_float` | `MTLPixelFormatRGBA16Float` |
| `r32_float` | `MTLPixelFormatR32Float` |
| `rgba32_float` | `MTLPixelFormatRGBA32Float` |
| `depth32_float` | `MTLPixelFormatDepth32Float` |

## Requirements

- macOS 12+
- Metal framework
- IOSurface framework
- CoreFoundation framework
