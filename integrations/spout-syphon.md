---
layout: default
title: Spout/Syphon Bridge (nozzle-spout-syphon)
---

[nozzle-spout-syphon](https://github.com/nozzle-io/nozzle-spout-syphon) is the planned bridge between nozzle and Syphon on macOS / Spout on Windows.

## Status

Phase 0 scaffold only. CI builds and packages an app shell for macOS and Windows, but the Syphon and Spout SDK integrations are not implemented yet.

| Direction | macOS | Windows | Linux |
|---|---|---|---|
| Syphon/Spout -> nozzle | 🟦 | 🟦 | N/A |
| nozzle -> Syphon/Spout | 🟦 | 🟦 | N/A |

🟦 means scaffold build/package only. It is not runtime bridge evidence and not a zero-copy claim.

## Required evidence before runtime support claims

- Syphon sender -> bridge -> nozzle-viewer.
- nozzle sender -> bridge -> Syphon receiver.
- Spout sender -> bridge -> nozzle-viewer.
- nozzle sender -> bridge -> Spout receiver.
- Non-square size, origin, channel order, alpha, disconnect/reconnect, and sender-name collision behavior.
