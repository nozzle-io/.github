---
layout: default
title: Format Support
---

Nozzle supports a range of texture formats for different use cases: standard 8-bit color, high-precision floating point, and depth.

## Supported Formats

| Format | Channels | Bytes/Pixel | Description |
|--------|----------|-------------|-------------|
| `r8_unorm` | 1 | 1 | Single-channel 8-bit unsigned normalized |
| `rg8_unorm` | 2 | 2 | Two-channel 8-bit unsigned normalized |
| `rgba8_unorm` | 4 | 4 | RGBA 8-bit unsigned normalized |
| `bgra8_unorm` | 4 | 4 | BGRA 8-bit unsigned normalized |
| `rgba8_srgb` | 4 | 4 | RGBA 8-bit sRGB encoded |
| `bgra8_srgb` | 4 | 4 | BGRA 8-bit sRGB encoded |
| `r16_unorm` | 1 | 2 | Single-channel 16-bit unsigned normalized |
| `rg16_unorm` | 2 | 4 | Two-channel 16-bit unsigned normalized |
| `rgba16_unorm` | 4 | 8 | RGBA 16-bit unsigned normalized |
| `r16_float` | 1 | 2 | Single-channel 16-bit float (half precision) |
| `rg16_float` | 2 | 4 | Two-channel 16-bit float |
| `rgba16_float` | 4 | 8 | RGBA 16-bit float (half precision) |
| `r32_float` | 1 | 4 | Single-channel 32-bit float |
| `rg32_float` | 2 | 8 | Two-channel 32-bit float |
| `rgba32_float` | 4 | 16 | RGBA 32-bit float (full precision) |
| `r32_uint` | 1 | 4 | Single-channel 32-bit unsigned integer |
| `rgba32_uint` | 4 | 16 | RGBA 32-bit unsigned integer |
| `depth32_float` | 1 | 4 | Depth-only 32-bit float |

## Backend Format Mapping

### macOS (Metal/IOSurface)

| Nozzle | Metal (MTLPixelFormat) |
|--------|------------------------|
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

### Windows (D3D11)

| Nozzle | DXGI_FORMAT |
|--------|-------------|
| `r8_unorm` | `DXGI_FORMAT_R8_UNORM` |
| `rg8_unorm` | `DXGI_FORMAT_R8G8_UNORM` |
| `rgba8_unorm` | `DXGI_FORMAT_R8G8B8A8_UNORM` |
| `bgra8_unorm` | `DXGI_FORMAT_B8G8R8A8_UNORM` |
| `rgba8_srgb` | `DXGI_FORMAT_R8G8B8A8_UNORM_SRGB` |
| `r16_float` | `DXGI_FORMAT_R16_FLOAT` |
| `rgba16_float` | `DXGI_FORMAT_R16G16B16A16_FLOAT` |
| `r32_float` | `DXGI_FORMAT_R32_FLOAT` |
| `rgba32_float` | `DXGI_FORMAT_R32G32B32A32_FLOAT` |
| `depth32_float` | `DXGI_FORMAT_D32_FLOAT` |

### Linux (DMA-BUF)

| Nozzle | DRM Fourcc |
|--------|------------|
| `r8_unorm` | `DRM_FORMAT_R8` |
| `rg8_unorm` | `DRM_FORMAT_GR88` |
| `rgba8_unorm` | `DRM_FORMAT_RGBA8888` |
| `bgra8_unorm` | `DRM_FORMAT_ARGB8888` |
| `r16_float` | `DRM_FORMAT_R16` |
| `rgba16_float` | `DRM_FORMAT_RGBA16161616F` |
| `r32_float` | `DRM_FORMAT_R32` |
| `rgba32_float` | `DRM_FORMAT_RGBA32323232F` |

## Format Fallback

When `allow_format_fallback` is `true` (default), the receiver accepts a format that differs from what it requested, falling back to the nearest compatible format. This is useful when sender and receiver run on different GPU vendors or different OS versions.

## Usage

```cpp
// C++
nozzle::texture_format fmt = nozzle::texture_format::rgba16_float;

// C
NozzleTextureFormat fmt = NOZZLE_FORMAT_RGBA16_FLOAT;
```
