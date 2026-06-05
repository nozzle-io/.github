---
layout: default
title: Nozzle Tester (nozzle-tester)
---

[nozzle-tester](https://github.com/nozzle-io/nozzle-tester) is the canonical conformance tool for nozzle runtime smoke evidence.

It is not a sample app. It provides shared pattern generation, oracle verification, CLI and GUI sender/receiver paths, and structured JSON evidence so issue reports can reference machine-readable results instead of screenshots and prose.

## Status

Initial cross-platform implementation. CI builds the CLI and GUI on macOS, Windows, and Linux and runs unit/self-test evidence generation.

## Features

- Hostile non-symmetric pattern for orientation, channel-order, alpha, stale-frame, and odd-size failures.
- CLI pattern, verify, self-test, sender, and receiver commands.
- GUI pattern preview, sender, receiver, and loopback modes.
- JSON evidence output with structured failure reasons.
- GUI evidence capture that writes JSON plus a captured RGBA frame artifact.

## Build

```bash
git clone --recursive https://github.com/nozzle-io/nozzle-tester.git
cd nozzle-tester
cmake -S . -B build -DNOZZLE_TESTER_BUILD_GUI=ON -DNOZZLE_TESTER_BUILD_TESTS=ON
cmake --build build --config Release
ctest --test-dir build --output-on-failure -C Release
```

## Evidence Boundary

A `PASS` from nozzle-tester proves only the exact tested case and captured frame. It is not a blanket interop-support claim for a binding, host app, backend, or platform.
