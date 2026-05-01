---
layout: default
title: OBS Studio (obs-nozzle)
---

[obs-nozzle](https://github.com/nozzle-io/obs-nozzle) is an OBS Studio plugin providing nozzle GPU texture sharing as both source and output.

## What It Does

- **Nozzle Receiver (Source)** — Receive GPU textures from any nozzle sender and display them in OBS
- **Nozzle Sender (Output)** — Send OBS rendered frames to any nozzle receiver

## Features

- Cross-platform: macOS (Metal/IOSurface), Windows (D3D11), Linux (DMA-BUF)
- Named sender/receiver model with automatic discovery
- No extra dependencies beyond OBS Studio and nozzle

## Build

### Prerequisites

- CMake 3.20+
- C++17 compiler
- OBS Studio development files

### Steps

```bash
git clone --recurse-submodules git@github.com:nozzle-io/obs-nozzle.git
cd obs-nozzle
cmake -B build \
    -DOBS_INCLUDE_DIR=/path/to/obs-studio/libobs \
    -DOBS_LIBRARY=/path/to/libobs.so
cmake --build build
```

### Platform Notes

**macOS (Homebrew):**
```bash
cmake -B build -DOBS_INCLUDE_DIR=/opt/homebrew/include/obs -DOBS_LIBRARY=/opt/homebrew/lib/libobs.0.dylib
```

**Linux:**
```bash
cmake -B build -DOBS_INCLUDE_DIR=/usr/include/obs -DOBS_LIBRARY=/usr/lib/x86_64-linux-gnu/libobs.so.0
```

**Windows:**
```bash
cmake -B build -DOBS_INCLUDE_DIR="C:/path/to/obs-studio/libobs" -DOBS_LIBRARY="C:/path/to/libobs.lib"
```

Or set `OBS_STUDIO_DIR` environment variable:
```bash
export OBS_STUDIO_DIR=/path/to/obs-studio
cmake -B build
```

## Installation

**macOS:**
```bash
cp -r build/obs-nozzle.so ~/Library/Application\ Support/obs-studio/plugins/obs-nozzle.plugin/
```

**Linux:**
```bash
cp build/obs-nozzle.so ~/.config/obs-studio/plugins/obs-nozzle/bin/64bit/
```

**Windows:**
```bash
copy build\obs-nozzle.dll "%APPDATA%\obs-studio\plugins\obs-nozzle\obs-plugins\64bit\"
```

## Usage

### Nozzle Receiver (Source)

1. Add a new source in OBS
2. Select "Nozzle Receiver"
3. Choose a sender from the dropdown (or type a sender name)
4. Adjust timeout if needed (default: 100ms)

### Nozzle Sender (Output)

1. Go to Settings → Output
2. Add a new output of type "Nozzle Sender"
3. Set the sender name and application name
4. Start the output
