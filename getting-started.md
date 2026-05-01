---
layout: default
title: Getting Started
---

## Requirements

- C++17 compiler (Clang, MSVC, GCC)
- CMake 3.20+
- macOS 12+ (Metal/IOSurface), Windows 10+ (D3D11), or Linux (glibc 2.31+, DRM/KMS for DMA-BUF)

## Build from Source

```bash
git clone https://github.com/nozzle-io/nozzle.git
cd nozzle
cmake -B build -DCMAKE_OSX_DEPLOYMENT_TARGET=12.0  # macOS only flag
cmake --build build
```

This produces a static library (`libnozzle.a` / `nozzle.lib`) and header files in `include/`.

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `NOZZLE_BUILD_OPENGL` | `ON` | Build OpenGL interop |
| `NOZZLE_BUILD_TESTS` | `ON` | Build unit + integration tests |
| `NOZZLE_BUILD_EXAMPLES` | `ON` | Build example programs |

### Run Tests

```bash
./build/tests/nozzle_tests --reporter compact
./build/tests/nozzle_integration_tests --reporter compact
```

## Integration

### CMake (add_subdirectory)

```cmake
add_subdirectory(path/to/nozzle)
target_link_libraries(my_app PRIVATE nozzle)
```

### CMake (find_package)

```cmake
# After installing nozzle
find_package(nozzle REQUIRED)
target_link_libraries(my_app PRIVATE nozzle::nozzle)
```

### Source Integration

Copy `include/nozzle/` into your project and link the static library. No runtime dependencies required.

## First Sender

```cpp
#include <nozzle/nozzle.hpp>

int main() {
    // Create a named sender
    auto sender_result = nozzle::sender::create({
        .name = "my_output",
        .application_name = "MyApp",
        .ring_buffer_size = 3
    });

    if (!sender_result.ok()) {
        // Handle error
        return 1;
    }
    auto sender = std::move(sender_result).value();

    // Acquire a writable frame
    auto frame_result = sender.acquire_writable_frame({
        .width = 1920,
        .height = 1080,
        .format = nozzle::texture_format::rgba8_unorm
    });

    if (!frame_result.ok()) {
        return 1;
    }
    auto frame = std::move(frame_result).value();

    // Write pixel data
    {
        auto pixels = nozzle::lock_writable_pixels(frame).value();
        auto *buf = static_cast<uint8_t *>(pixels.data);
        for (uint32_t i = 0; i < pixels.width * pixels.height * 4; i += 4) {
            buf[i + 0] = 255; // R
            buf[i + 1] = 128; // G
            buf[i + 2] = 64;  // B
            buf[i + 3] = 255; // A
        }
    } // pixels unlocked here

    // Publish the frame
    sender.commit_frame(frame);

    return 0;
}
```

## First Receiver

```cpp
#include <nozzle/nozzle.hpp>
#include <iostream>

int main() {
    // Create a receiver that connects to a named sender
    auto receiver_result = nozzle::receiver::create({
        .name = "my_output",
        .application_name = "MyViewer",
        .receive_mode_val = nozzle::receive_mode::latest_only
    });

    if (!receiver_result.ok()) {
        return 1;
    }
    auto receiver = std::move(receiver_result).value();

    // Poll for frames
    while (true) {
        auto frame_result = receiver.acquire_frame({
            .timeout_ms = 1000
        });

        if (!frame_result.ok()) {
            std::cerr << "Error: " << frame_result.error().message << "\n";
            continue;
        }

        auto frame = std::move(frame_result).value();
        auto info = frame.info();

        std::cout << "Frame #" << info.frame_index
                  << " (" << info.width << "x" << info.height << ")"
                  << " format=" << static_cast<int>(info.format)
                  << "\n";

        frame.release();
    }

    return 0;
}
```

## Discovery

List all available senders on the local machine:

```cpp
#include <nozzle/nozzle.hpp>

auto senders = nozzle::enumerate_senders();
for (const auto &s : senders) {
    std::cout << s.name << " (" << s.application_name << ")\n";
}
```

## Error Handling

All fallible operations return `nozzle::Result<T>`. Always check the result:

```cpp
auto result = nozzle::sender::create(desc);
if (!result.ok()) {
    auto err = result.error();
    // err.code    -> nozzle::ErrorCode
    // err.message -> std::string description
    std::cerr << "Error " << static_cast<int>(err.code) << ": " << err.message << "\n";
    return;
}
auto sender = std::move(result).value();
```

## Next Steps

- [C++ API Reference](api/cpp.html) &mdash; Full C++ API documentation
- [C API Reference](api/c.html) &mdash; C ABI for plugin integration
- [Backends](backends/metal.html) &mdash; Metal/IOSurface, D3D11, DMA-BUF details
- [Integrations](integrations/python.html) &mdash; Python, Rust, Swift, openFrameworks, and more
- [Format Support](format-support.html) &mdash; Supported texture formats
