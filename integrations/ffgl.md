---
layout: default
title: FFGL / Resolume (nozzle-ffgl)
---

[nozzle-ffgl](https://github.com/nozzle-io/nozzle-ffgl) provides first-party FFGL plugins for hosts such as Resolume.

## Plugins

| Plugin | FFGL type | Purpose |
|---|---|---|
| `NozzleReceive` | Source | Receives a named nozzle source and renders it as an FFGL source. |
| `NozzleSend` | Effect | Publishes the incoming FFGL texture as a nozzle source and draws pass-through output. |

## Status

| Module | macOS | Windows | Linux |
|---|---|---|---|
| `NozzleReceive` | 🟦 | 🟦 | N/A |
| `NozzleSend` | 🟦 | 🟦 | N/A |

🟦 means CI build/package only. Real Resolume loading, orientation, channel order, alpha, and non-square test-pattern smoke evidence is still required before this should be marked ✅.

## Install

Copy the plugins from the release zip into Resolume's Extra Effects folder.

macOS:

```text
~/Documents/Resolume/Extra Effects/NozzleReceive.bundle
~/Documents/Resolume/Extra Effects/NozzleSend.bundle
```

Windows:

```text
%USERPROFILE%\Documents\Resolume\Extra Effects\NozzleReceive.dll
%USERPROFILE%\Documents\Resolume\Extra Effects\NozzleSend.dll
```

Restart the FFGL host after installing.

## Performance and format notes

- macOS uses nozzle's CGL/IOSurface OpenGL interop path.
- Windows is currently a functional CPU-copy bridge through nozzle OpenGL/D3D11 interop, not zero-copy.
- Linux is out of scope for the first Resolume-focused FFGL pass.
- First-pass format scope is `rgba8_unorm`; 16F/32F support is not claimed.

## Validation matrix required before ✅

1. Resolume loads both plugins on macOS and Windows.
2. `NozzleSend -> nozzle-viewer` displays a moving test pattern.
3. known nozzle sender -> `NozzleReceive` displays in Resolume.
4. test pattern proves no vertical flip and no R/B swap.
5. alpha behavior is documented.
6. at least one non-square resolution is verified.
7. disconnect/reconnect does not leak state or leave stale frames.
