---
layout: default
title: Compute and copy costs
---

# Compute and copy costs

Nozzle supports several texture-transfer paths, but not every integration has the same per-frame cost or the same level of runtime evidence.

The canonical cost matrix lives in nozzle-dev:

- [Compute/copy cost matrix](https://github.com/nozzle-io/nozzle-dev/blob/main/docs/compute-cost-matrix.md)

Use that matrix to distinguish:

- `ZERO_COPY` shared native resource paths;
- `GPU_COPY` blit/copy/render-to-texture paths;
- `CPU_READBACK_UPLOAD` paths that cross CPU memory;
- `HOST_STAGING` build/package/host-loader staging work;
- `UNVERIFIED` paths that are intended or buildable but not runtime-proven;
- `UNSUPPORTED` paths that are explicitly out of scope.

The public site intentionally links to the canonical source instead of duplicating the full table. If the nozzle-dev matrix changes, update the canonical document first and keep this page as the stable public entry point.
