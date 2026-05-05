---
layout: default
title: Zig (nozzle.zig)
---

[nozzle.zig](https://github.com/nozzle-io/nozzle.zig) provides Zig bindings for nozzle with native error unions and type-safe wrappers.

## Setup

```bash
git clone https://github.com/nozzle-io/nozzle.zig.git
cd nozzle.zig
zig build
```

Or use as a dependency in your `build.zig.zon`:

```zig
// build.zig.zon
.{
    .name = "my-app",
    .version = "0.1.0",
    .dependencies = .{
        .nozzle = .{
            .url = "https://github.com/nozzle-io/nozzle.zig/archive/refs/heads/main.tar.gz",
        },
    },
    .paths = .{""},
}
```

## Requirements

- Zig 0.13+
- C++17 compiler (clang / MSVC)
- macOS 12+ / Windows 10+ / Linux

No CMake required — `build.zig` compiles nozzle from source directly.

## Sender

```zig
const nozzle = @import("nozzle");

const sender = try nozzle.Sender.create(.{
    .name = "my_sender",
    .application_name = "MyApp",
    .ring_buffer_size = 3,
});
defer sender.destroy();

const frame = try sender.acquireWritableFrame(1920, 1080, .rgba8_unorm);
// ... write GPU data into frame ...
try sender.commitFrame(frame);
```

## Receiver

```zig
const nozzle = @import("nozzle");

const receiver = try nozzle.Receiver.create(.{
    .name = "my_sender",
    .application_name = "MyViewer",
});
defer receiver.destroy();

const frame = try receiver.acquireFrame(.{ .timeout_ms = 1000 });
defer frame.release();

const info = try frame.info();
// info.width == 1920, info.height == 1080
```

## Error Handling

All fallible operations return Zig error unions. C error codes map directly:

```zig
const frame = nozzle.Sender.acquireWritableFrame(0, 0, .unknown) catch |err| {
    switch (err) {
        error.InvalidArgument => { /* handle */ },
        error.UnsupportedFormat => { /* handle */ },
        else => { /* handle */ },
    }
};
```

## Features

- Zig-native error unions (no error code checking)
- Type-safe enums for formats, backends, and frame status
- Automatic resource cleanup with `defer`
- No CMake dependency — `build.zig` compiles everything
- Thread-safe (Sender and Receiver are safe to share across threads)

## Platform Support

| Platform | Backend | Status |
|----------|---------|--------|
| macOS 12+ | Metal/IOSurface | ✅ |
| Windows 10+ | D3D11 | ✅ |
| Linux | DMA-BUF | ✅ |
