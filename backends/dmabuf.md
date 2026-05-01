---
layout: default
title: DMA-BUF Backend
---

The Linux backend uses **DMA-BUF** for cross-process GPU texture sharing via GBM and EGL.

## Overview

DMA-BUF is a Linux kernel feature for sharing buffers between devices and processes. Nozzle uses GBM (Generic Buffer Manager) to allocate DMA-BUF buffers and EGL to create GPU textures from them.

## How It Works

```
Sender Process                              Receiver Process
─────────────────                          ─────────────────
GBM Device                                 GBM Device
    │                                           │
    ├── Allocate DMA-BUF via GBM                │
    ├── Create EGLImage from DMA-BUF            │
    ├── Render into texture                     │
    ├── Publish DMA-BUF fd                      │
    │      via shared state                     │
    │                                           ├── Receive DMA-BUF fd
    │                                           ├── Create EGLImage
    │                                           ├── Read texture
    │                                           │
    └── Ring buffer (N buffers)                 └── Frame acquisition
```

## Thread Safety

Synchronization is managed through the shared state ring buffer with atomic counters. DMA-BUF file descriptors are duplicated between processes.

## Zero-Copy

Texture data stays in GPU-accessible memory. DMA-BUF file descriptors allow both processes to reference the same buffer without copying. Transfer mode is `zero_copy_shared_texture`.

## Backend API

```cpp
#include <nozzle/backends/linux.hpp>

namespace nozzle::dma_buf {

Result<device> wrap_device(const device_desc &desc);
Result<texture> wrap_texture(const texture_wrap_desc &desc);
void *get_egl_image(const texture &tex);
int get_dmabuf_fd(const texture &tex);

}
```

### device_desc

```cpp
struct device_desc {
    void *gbm_device{nullptr};  // struct gbm_device *
};
```

### texture_wrap_desc

```cpp
struct texture_wrap_desc {
    void *egl_image{nullptr};   // EGLImage
    int dmabuf_fd{-1};          // DMA-BUF file descriptor
    uint32_t fourcc{0};         // DRM fourcc code
    uint32_t stride{0};         // Row stride in bytes
    uint64_t modifier{0};       // DRM format modifier
    uint32_t width{0};
    uint32_t height{0};
};
```

### wrap_device

Wrap an existing GBM device.

```cpp
Result<device> wrap_device(const device_desc &desc);
```

```cpp
auto dev = nozzle::dma_buf::wrap_device({
    .gbm_device = gbm_dev
}).value();
```

### wrap_texture

Wrap an existing DMA-BUF-backed texture.

```cpp
Result<texture> wrap_texture(const texture_wrap_desc &desc);
```

### get_egl_image / get_dmabuf_fd

Extract native handles from a nozzle texture.

```cpp
void *get_egl_image(const texture &tex);
int get_dmabuf_fd(const texture &tex);
```

## OpenGL Interop

Linux GL interop uses DMA-BUF mmap for texture transfer:

```cpp
#include <nozzle/backends/opengl.hpp>

nozzle::gl::gl_texture_desc gl_desc{
    .name = gl_texture_name,
    .target = GL_TEXTURE_2D,
    .width = 1920,
    .height = 1080,
    .format = nozzle::texture_format::rgba8_unorm
};

// Publish GL texture → DMA-BUF mmap → shared buffer
nozzle::gl::publish_gl_texture(sender, gl_desc);

// Copy received frame → DMA-BUF → glTexSubImage2D
auto frame = receiver.acquire_frame({.timeout_ms = 1000}).value();
nozzle::gl::copy_frame_to_gl_texture(frame, gl_desc);
```

## DRM Format Codes

| Nozzle Format | DRM Fourcc |
|---------------|------------|
| `r8_unorm` | `DRM_FORMAT_R8` |
| `rg8_unorm` | `DRM_FORMAT_GR88` |
| `rgba8_unorm` | `DRM_FORMAT_RGBA8888` |
| `bgra8_unorm` | `DRM_FORMAT_ARGB8888` |
| `r16_float` | `DRM_FORMAT_R16` |
| `rgba16_float` | `DRM_FORMAT_RGBA16161616F` |
| `r32_float` | `DRM_FORMAT_R32` |
| `rgba32_float` | `DRM_FORMAT_RGBA32323232F` |

## Requirements

- Linux with DRM/KMS support
- glibc 2.31+
- GBM library (`libgbm`)
- EGL
- Mesa or compatible GPU driver with DMA-BUF support
