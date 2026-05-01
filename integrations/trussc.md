---
layout: default
title: TrussC (tcxNozzle)
---

[tcxNozzle](https://github.com/nozzle-io/tcxNozzle) provides nozzle GPU texture sharing for [TrussC](https://github.com/TrussC-org/TrussC) applications.

## Setup

Add to your TrussC project's `addons.make`:

```
tcxNozzle
```

Or use as a CMake subdirectory. nozzle is included as a submodule.

## Sender

```cpp
#include "tcxNozzle.h"

tcx::NozzleSender sender;
sender.setup("myApp", width, height);

// Send from Pixels
sender.send(pixels);

// Send from FBO
sender.send(fbo);
```

## Receiver

```cpp
#include "tcxNozzle.h"

// Discover senders
auto senders = tcx::NozzleReceiver::findSenders();

// Connect
tcx::NozzleReceiver receiver;
receiver.connect("myApp");

// Receive into Texture
tc::Texture tex;
if (receiver.receive(tex)) {
    tex.draw(0, 0);
}
```

## API

| Class | Key Methods |
|-------|-------------|
| `tcx::NozzleSender` | `setup()`, `send(Pixels&)`, `send(Fbo&)`, `send(data, w, h)` |
| `tcx::NozzleReceiver` | `findSenders()`, `connect()`, `receive(Pixels&)`, `receive(Texture&)` |

## Platforms

- macOS (Metal/IOSurface)
- Windows (D3D11)
