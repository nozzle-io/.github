---
layout: default
title: Rust (nozzle.rs)
---

[nozzle.rs](https://github.com/nozzle-io/nozzle.rs) provides Rust bindings for nozzle via the C ABI.

## Setup

Add to `Cargo.toml`:

```toml
[dependencies]
nozzle = { git = "https://github.com/nozzle-io/nozzle.rs.git" }
```

## Requirements

- Rust stable
- C++17 compiler (clang / MSVC)
- CMake 3.20+
- macOS 12+ / Windows 10+

## Sender

```rust
use nozzle::*;

let mut sender = Sender::create(&SenderDesc {
    name: "my_sender".into(),
    application_name: "MyApp".into(),
    ..Default::default()
})?;

let frame = sender.acquire_writable_frame(1920, 1080, TextureFormat::Rgba8Unorm)?;
// ... write GPU data into frame ...
sender.commit_frame(frame)?;
```

## Receiver

```rust
use nozzle::*;

let mut receiver = Receiver::create(&ReceiverDesc {
    name: "my_sender".into(),
    application_name: "MyViewer".into(),
    ..Default::default()
})?;

let frame = receiver.acquire_frame(&AcquireDesc { timeout_ms: 1000 })?;
let info = frame.info()?;
println!("{}x{} frame #{}", info.width, info.height, info.frame_index);
```

## Discovery

```rust
use nozzle::*;

let senders = enumerate_senders()?;
for s in &senders {
    println!("sender: {} ({} via {:?})", s.name, s.id, s.backend);
}
```

## CPU Pixel Access

```rust
use nozzle::*;

let mut frame = sender.acquire_writable_frame(512, 512, TextureFormat::Rgba8Unorm)?;
{
    let mut pixels = frame.lock_writable_pixels()?;
    for y in 0..pixels.height {
        let row = pixels.row_mut(y).unwrap();
        for b in row.iter_mut() {
            *b = 0xFF;
        }
    }
}
sender.commit_frame(frame)?;
```

## Error Handling

All fallible operations return `nozzle::Result<T>`:

```rust
match sender.acquire_writable_frame(0, 0, TextureFormat::Unknown) {
    Err(e) => {
        assert_eq!(e.code, ErrorCode::InvalidArgument);
        eprintln!("{}", e);
    }
    Ok(_) => unreachable!(),
}
```

## Texture Formats

| Format | Bytes/Pixel |
|--------|-------------|
| `R8Unorm` | 1 |
| `RG8Unorm` | 2 |
| `Rgba8Unorm` / `Bgra8Unorm` | 4 |
| `R16Float` | 2 |
| `Rgba16Float` | 8 |
| `R32Float` | 4 |
| `Rgba32Float` | 16 |

## Thread Safety

`Sender` and `Receiver` implement `Send + Sync`. Safe to call from multiple threads.

## Platform Notes

- **macOS**: Links Metal, IOSurface, Foundation frameworks automatically
- **Windows**: Links d3d11, dxgi, ole32, user32 automatically
