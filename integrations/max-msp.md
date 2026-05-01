---
layout: default
title: Max/MSP (jit.nozzle)
---

[jit.nozzle](https://github.com/nozzle-io/jit.nozzle) provides Max/MSP externals for inter-process matrix and texture sharing via nozzle.

## Externals

### jit.nozzle.send

Accepts `jit.matrix` input and publishes pixel data to named shared streams.

```
[jit.matrix]  ──►  jit.nozzle.send  ──►  [width height frame_index]
                 @name "myStream"
```

| Attribute | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | symbol | `"nozzle_sender"` | Sender name for discovery |

| Message | Description |
|---------|-------------|
| `jit_matrix` | Receive a jit.matrix and publish its pixel data |
| `dump` | Print current status to console |

### jit.gl.nozzle.send

Accepts `jit.gl.texture` input and publishes the OpenGL texture.

```
[jit_gl_texture name]  ──►  jit.gl.nozzle.send  ──►  [width height frame_index]
                          @name "myStream"
```

| Attribute | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | symbol | `"nozzle_sender"` | Sender name for discovery |

| Message | Description |
|---------|-------------|
| `jit_gl_texture` | Receive a jit.gl.texture name and publish its GL texture |
| `bang` | Re-publish the last cached texture |
| `dump` | Print current status to console |

### jit.gl.nozzle.receive

Receives GL texture data from a named sender. Outputs `jit_gl_texture` on the left outlet, frame info on the right outlet.

```
[draw]  ──►  jit.gl.nozzle.receive  ──►  [jit_gl_texture output]
             @name "myStream"             ──►  [frame info events]
             @out_name "nozzle_recv_tex"
             @timeout 0
```

| Attribute | Type | Default | Description |
|-----------|------|---------|-------------|
| `name` | symbol | `"nozzle_sender"` | Sender name to connect to |
| `out_name` | symbol | `"nozzle_recv_tex"` | Name of the output jit.gl.texture |
| `timeout` | int | `0` | Frame acquisition timeout in ms (0 = non-blocking) |

| Message | Description |
|---------|-------------|
| `bang` | Poll for new frame (outputs frame info, no GL texture copy) |
| `draw` | Acquire frame, copy to internal GL texture, output `jit_gl_texture` |
| `connect` | Reconnect to sender |
| `info` | Print connected sender info to console |

## Build

```bash
git clone --recursive https://github.com/nozzle-io/jit.nozzle.git
cd jit.nozzle
cmake -B build
cmake --build build
```

Output: `externals/` with `.mxo` bundles (macOS) or `.mxe64` files (Windows).

## Requirements

- CMake 3.19+
- C++17 compiler
- macOS 12.0+ or Windows 10+
- Max 8.0+

## Installation

Copy the `externals/` and `help/` folders into your Max packages directory.

## Architecture

```
jit.nozzle.send:        jit_matrix → lock_pixels → memcpy → commit_frame
jit.nozzle.receive:     acquire_frame → lock_pixels → memcpy → jit.matrix → output
jit.gl.nozzle.send:     jit_gl_texture → get GL name → nozzle_sender_publish_gl_texture
jit.gl.nozzle.receive:  acquire_frame → nozzle_frame_copy_to_gl_texture → jit_gl_texture output
```

The externals use the nozzle C ABI to avoid exception/RTTI conflicts with Max's runtime.
