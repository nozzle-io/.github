---
layout: default
title: Nozzle Viewer (nozzle-viewer)
---

[nozzle-viewer](https://github.com/nozzle-io/nozzle-viewer) is a lightweight desktop app for discovering and previewing active nozzle sources.

## Status

Initial cross-platform implementation. CI builds and tests on macOS, Windows, and Linux.

## Features

- Lists currently discoverable nozzle senders.
- Connects receiver sessions to each source.
- Displays live previews for RGBA/BGRA sources through nozzle CPU pixel readback.
- Switches between all-source grid view and focused single-source view.

## Build

```bash
git clone --recursive https://github.com/nozzle-io/nozzle-viewer.git
cd nozzle-viewer
cmake -S . -B build -DNOZZLE_VIEWER_BUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```

## Platform Notes

- macOS: Metal/IOSurface receiver backend, Metal ImGui renderer.
- Windows: D3D11 receiver backend, D3D11 ImGui renderer.
- Linux: DMA-BUF receiver backend, OpenGL ImGui renderer.

A source remains visible even when live preview cannot be acquired, so discovery/debugging is still useful for incompatible backends, unsupported formats, and senders that have not produced frames yet.
