---
layout: default
title: PureData / GEM (nozzle-pd)
---

[nozzle-pd](https://github.com/nozzle-io/nozzle-pd) provides PureData/GEM externals for inter-process texture sharing via nozzle.

## Objects

### pix_nozzle_send

Accepts GEM pix image data (CPU path) and publishes to a named shared stream. Handles RGB→RGBA conversion automatically.

```
[gemhead]
|
[pix_video]
|
[pix_nozzle_send my_sender_name]
```

| Message | Description |
|---------|-------------|
| `name <symbol>` | Set sender name (default: `"nozzle_sender"`) |

### pix_nozzle_receive

Receives nozzle frames (CPU path) and injects into the GEM render chain as a pixBlock.

```
[gemhead]
|
[pix_nozzle_receive my_sender_name]
|
[pix_texture]
```

| Message | Description |
|---------|-------------|
| `name <symbol>` | Set sender name to connect to (default: `"nozzle_sender"`) |

### pix_nozzle_gl_send

Grabs the currently bound OpenGL texture from the render chain and publishes it via nozzle (GPU path). Place after `pix_texture`.

```
[gemhead]
|
[pix_video]
|
[pix_texture]
|
[pix_nozzle_gl_send my_sender_name]
```

| Message | Description |
|---------|-------------|
| `name <symbol>` | Set sender name (default: `"nozzle_sender"`) |

### pix_nozzle_gl_receive

Receives nozzle frames and copies to an OpenGL texture (GPU path), then injects into the GEM render chain.

```
[gemhead]
|
[pix_nozzle_gl_receive my_sender_name]
|
[pix_texture]
```

| Message | Description |
|---------|-------------|
| `name <symbol>` | Set sender name to connect to (default: `"nozzle_sender"`) |

## Build

```bash
git clone --recursive https://github.com/nozzle-io/nozzle-pd.git
cd nozzle-pd
make
```

Output: `.build/` with `.pd_darwin` (macOS) or `.pd_linux` (Linux) externals.

To build against local GEM source:

```bash
make GEM_DIR=/path/to/Gem PD_DIR=/path/to/pure-data
```

## Requirements

- C++17 compiler
- PureData + GEM (v0.94+)
- macOS 12.0+ or Linux

## Installation

Copy the built externals to your Pd externals directory:

```bash
cp .build/pix_nozzle_* ~/.pd-externals/nozzle-pd/
```

Then add `~/.pd-externals/nozzle-pd` to Pd's search path.

## Supported Formats

| GEM Format | Nozzle Format |
|---|---|
| GL_UNSIGNED_BYTE, 1ch (LUMINANCE) | R8_UNORM |
| GL_UNSIGNED_BYTE, 2ch (LUMINANCE_ALPHA) | RG8_UNORM |
| GL_UNSIGNED_BYTE, 3ch (RGB) | RGBA8_UNORM (auto-converted) |
| GL_UNSIGNED_BYTE, 4ch (RGBA) | RGBA8_UNORM |
| GL_UNSIGNED_SHORT, 1-4ch | R16/RG16/RGBA16_UNORM |
| GL_HALF_FLOAT, 1-4ch | R16F/RG16F/RGBA16_FLOAT |
| GL_FLOAT, 1-4ch | R32F/RG32F/RGBA32_FLOAT |

## Architecture

```
pix_nozzle_send:        GemState pixBlock → lock_writable_pixels → memcpy → commit_frame
pix_nozzle_receive:     acquire_frame → lock_pixels → memcpy → GemState pixBlock
pix_nozzle_gl_send:     glGetIntegerv(GL_TEXTURE_BINDING_2D) → nozzle_sender_publish_gl_texture
pix_nozzle_gl_receive:  acquire_frame → nozzle_frame_copy_to_gl_texture → GemState pixBlock
```

The externals use the nozzle C ABI exclusively. GEM objects are compiled with RTTI and exceptions enabled (required by GEM headers), while the nozzle static library is compiled without them.
