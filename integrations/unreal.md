---
layout: default
title: Unreal Engine (nozzle-unreal)
---

[nozzle-unreal](https://github.com/nozzle-io/nozzle-unreal) is a Phase 0 scaffold for a future Unreal Engine plugin.

## Status

Static package-shape CI only. The repository contains a `.uplugin`, runtime/editor module skeletons, a sample project skeleton, and documentation, but it does not run Unreal BuildPlugin, compile against Unreal Engine, link nozzle, or prove a texture path.

| Target | macOS | Windows | Linux |
|---|---|---|---|
| Unreal Engine plugin scaffold | N/A | 🟦 | N/A |
| Runtime sender/receiver | N/A | Missing | N/A |

The first real target is Win64 + D3D11. D3D12 support is not claimed.

## Required evidence before runtime support claims

- Unreal sender -> nozzle-viewer in Editor PIE and packaged Development builds.
- Known nozzle sender -> Unreal render target/material in Editor PIE and packaged Development builds.
- D3D11 RHI, native texture format, transfer mode, origin, R/B order, alpha, and cleanup behavior recorded.
