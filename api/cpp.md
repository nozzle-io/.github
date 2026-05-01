---
layout: default
title: C++ API
---

All types are in the `nozzle` namespace. Include the umbrella header:

```cpp
#include <nozzle/nozzle.hpp>
```

---

## Error Handling

### `Result<T>`

All fallible operations return `Result<T>`. Check `ok()` before accessing the value.

```cpp
auto result = nozzle::sender::create(desc);
if (!result.ok()) {
    auto &err = result.error();
    // err.code    -> ErrorCode
    // err.message -> std::string
    return;
}
auto sender = std::move(result).value();
```

### `Result<void>`

Operations that don't return a value on success use `Result<void>`:

```cpp
auto result = sender.commit_frame(frame);
if (!result.ok()) { /* handle error */ }
```

### `ErrorCode`

| Value | Description |
|-------|-------------|
| `Ok` | Success |
| `Unknown` | Unclassified error |
| `InvalidArgument` | Bad parameter |
| `UnsupportedBackend` | Backend not available on this platform |
| `UnsupportedFormat` | Format not supported by device |
| `DeviceMismatch` | Texture from wrong device |
| `ResourceCreationFailed` | GPU resource allocation failed |
| `SharedHandleFailed` | Cross-process handle sharing failed |
| `SenderNotFound` | No sender with given name |
| `SenderClosed` | Sender no longer alive |
| `Timeout` | Operation timed out |
| `BackendError` | Platform-specific GPU error |

---

## Types

### Enums

#### `backend_type`

```cpp
enum class backend_type {
    unknown,
    d3d11,
    metal,
    opengl,
    dma_buf,
};
```

#### `texture_format`

```cpp
enum class texture_format {
    unknown,
    r8_unorm,
    rg8_unorm,
    rgba8_unorm,
    bgra8_unorm,
    rgba8_srgb,
    bgra8_srgb,
    r16_unorm,
    rg16_unorm,
    rgba16_unorm,
    r16_float,
    rg16_float,
    rgba16_float,
    r32_float,
    rg32_float,
    rgba32_float,
    r32_uint,
    rgba32_uint,
    depth32_float,
};
```

#### `transfer_mode`

```cpp
enum class transfer_mode {
    unknown,
    zero_copy_shared_texture,
    gpu_copy,
    cpu_copy,
};
```

#### `sync_mode`

```cpp
enum class sync_mode {
    none,
    access_guarded,
    gpu_fence_best_effort,
};
```

#### `receive_mode`

```cpp
enum class receive_mode {
    latest_only,
    sequential_best_effort,
};
```

#### `frame_status`

```cpp
enum class frame_status {
    new_frame,
    no_new_frame,
    dropped_frames,
    sender_closed,
    error,
};
```

#### `texture_usage`

Bitfield. Combine with `operator|`.

```cpp
enum class texture_usage : uint32_t {
    none = 0,
    shader_read = 1 << 0,
    shader_write = 1 << 1,
    render_target = 1 << 2,
    shared = 1 << 3,
};
```

### Structs

#### `frame_info`

```cpp
struct frame_info {
    uint64_t frame_index{0};
    uint64_t timestamp_ns{0};
    uint32_t width{0};
    uint32_t height{0};
    texture_format format{texture_format::unknown};
    transfer_mode transfer_mode_val{transfer_mode::unknown};
    sync_mode sync_mode_val{sync_mode::none};
    uint32_t dropped_frame_count{0};
};
```

#### `texture_desc`

```cpp
struct texture_desc {
    uint32_t width{0};
    uint32_t height{0};
    texture_format format{texture_format::unknown};
    texture_usage usage{texture_usage::shader_read | texture_usage::shared};
};
```

#### `texture_layout`

```cpp
struct texture_layout {
    uint32_t row_pitch_bytes{0};
    uint32_t slice_pitch_bytes{0};
    uint32_t alignment_bytes{0};
};
```

#### `sender_info`

```cpp
struct sender_info {
    std::string name{};
    std::string application_name{};
    std::string id{};
    backend_type backend{backend_type::unknown};
};
```

#### `connected_sender_info`

```cpp
struct connected_sender_info {
    std::string name{};
    std::string application_name{};
    std::string id{};
    backend_type backend{backend_type::unknown};
    uint32_t width{0};
    uint32_t height{0};
    texture_format format{texture_format::unknown};
    double estimated_fps{0.0};
    uint64_t frame_counter{0};
    uint64_t last_update_time_ns{0};
};
```

#### `sender_desc`

```cpp
struct sender_desc {
    std::string name{};
    std::string application_name{};
    uint32_t ring_buffer_size{3};
    metadata_list metadata{};
    bool allow_format_fallback{true};
};
```

#### `receiver_desc`

```cpp
struct receiver_desc {
    std::string name{};
    std::string application_name{};
    receive_mode receive_mode_val{receive_mode::latest_only};
};
```

#### `acquire_desc`

```cpp
struct acquire_desc {
    uint64_t timeout_ms{0};
};
```

#### `key_value`

```cpp
struct key_value {
    std::string key{};
    std::string value{};
};
```

`metadata_list` is `std::vector<key_value>`.

---

## sender

```cpp
class sender {
public:
    static Result<sender> create(const sender_desc &desc);
    ~sender();

    sender();
    sender(const sender &) = delete;
    sender &operator=(const sender &) = delete;
    sender(sender &&) noexcept;
    sender &operator=(sender &&) noexcept;

    Result<void> publish_external_texture(const texture &tex);
    Result<writable_frame> acquire_writable_frame(const texture_desc &desc);
    Result<void> commit_frame(writable_frame &frame);
    sender_info info() const;
    Result<void> set_metadata(const metadata_list &metadata);
    bool valid() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### `sender::create`

Creates a named sender with the given descriptor.

```cpp
static Result<sender> create(const sender_desc &desc);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `desc` | `const sender_desc &` | Sender configuration |

**Returns:** `Result<sender>` &mdash; the sender on success, error on failure.

### `publish_external_texture`

Publish a user-owned texture (created via backend `wrap_texture`).

```cpp
Result<void> publish_external_texture(const texture &tex);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `tex` | `const texture &` | External texture to publish |

**Returns:** `Result<void>`

### `acquire_writable_frame`

Acquire a nozzle-owned writable frame for GPU rendering.

```cpp
Result<writable_frame> acquire_writable_frame(const texture_desc &desc);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `desc` | `const texture_desc &` | Desired texture dimensions and format |

**Returns:** `Result<writable_frame>` &mdash; frame ready for writing on success.

### `commit_frame`

Publish a writable frame to receivers.

```cpp
Result<void> commit_frame(writable_frame &frame);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `frame` | `writable_frame &` | Frame to commit |

**Returns:** `Result<void>`

### `info`

Get sender metadata.

```cpp
sender_info info() const;
```

**Returns:** `sender_info`

### `set_metadata`

Update sender metadata visible to receivers.

```cpp
Result<void> set_metadata(const metadata_list &metadata);
```

### `valid`

Check if the sender is initialized.

```cpp
bool valid() const;
```

---

## receiver

```cpp
class receiver {
public:
    static Result<receiver> create(const receiver_desc &desc);
    ~receiver();

    receiver();
    receiver(const receiver &) = delete;
    receiver &operator=(const receiver &) = delete;
    receiver(receiver &&) noexcept;
    receiver &operator=(receiver &&) noexcept;

    Result<frame> acquire_frame();
    Result<frame> acquire_frame(const acquire_desc &desc);
    connected_sender_info connected_info() const;
    metadata_list sender_metadata() const;
    bool is_connected() const;
    bool valid() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### `receiver::create`

Creates a receiver that connects to a named sender.

```cpp
static Result<receiver> create(const receiver_desc &desc);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `desc` | `const receiver_desc &` | Receiver configuration. `name` matches the sender to connect to. |

**Returns:** `Result<receiver>`

### `acquire_frame`

Acquire the latest frame from the connected sender.

```cpp
Result<frame> acquire_frame();
Result<frame> acquire_frame(const acquire_desc &desc);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `desc` | `const acquire_desc &` | Timeout configuration. `timeout_ms = 0` for non-blocking. |

**Returns:** `Result<frame>` &mdash; acquired frame on success.

### `connected_info`

Get information about the connected sender.

```cpp
connected_sender_info connected_info() const;
```

**Returns:** `connected_sender_info`

### `sender_metadata`

Get metadata from the connected sender.

```cpp
metadata_list sender_metadata() const;
```

### `is_connected`

Check if the receiver is currently connected to a live sender.

```cpp
bool is_connected() const;
```

---

## frame

```cpp
class frame {
public:
    frame();
    ~frame();

    frame(const frame &) = delete;
    frame &operator=(const frame &) = delete;
    frame(frame &&) noexcept;
    frame &operator=(frame &&) noexcept;

    frame_info info() const;
    const texture &get_texture() const;
    bool valid() const;
    Result<texture> clone_to_owned_texture(device &dev) const;
    void release();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### `info`

Get frame metadata (dimensions, format, frame index, timestamp).

```cpp
frame_info info() const;
```

### `get_texture`

Access the underlying shared texture.

```cpp
const texture &get_texture() const;
```

### `clone_to_owned_texture`

Create a GPU copy of the frame's texture as an owned texture.

```cpp
Result<texture> clone_to_owned_texture(device &dev) const;
```

### `release`

Explicitly release the frame. Also called automatically on destruction.

```cpp
void release();
```

---

## writable_frame

```cpp
class writable_frame {
public:
    writable_frame() noexcept;
    ~writable_frame();

    writable_frame(const writable_frame &) = delete;
    writable_frame &operator=(const writable_frame &) = delete;
    writable_frame(writable_frame &&) noexcept;
    writable_frame &operator=(writable_frame &&) noexcept;

    texture &get_texture();
    const texture_desc &desc() const;
    bool valid() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### `get_texture`

Access the writable texture for GPU rendering.

```cpp
texture &get_texture();
```

### `desc`

Get the descriptor used to create this frame.

```cpp
const texture_desc &desc() const;
```

---

## texture

```cpp
class texture {
public:
    texture();
    ~texture();

    texture(const texture &) = delete;
    texture &operator=(const texture &) = delete;
    texture(texture &&) noexcept;
    texture &operator=(texture &&) noexcept;

    const texture_desc &desc() const;
    texture_layout layout() const;
    bool valid() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### `desc`

Get texture descriptor (dimensions, format, usage flags).

```cpp
const texture_desc &desc() const;
```

### `layout`

Get texture memory layout (row pitch, slice pitch, alignment).

```cpp
texture_layout layout() const;
```

---

## device

```cpp
class device {
public:
    static Result<device> default_device();
    ~device();

    device();
    device(const device &) = delete;
    device &operator=(const device &) = delete;
    device(device &&) noexcept;
    device &operator=(device &&) noexcept;

    bool supports_format(texture_format format, texture_usage usage) const;
    bool supports_native_format(uint32_t native_format, texture_usage usage) const;
    bool valid() const;

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
};
```

### `default_device`

Get the system default GPU device.

```cpp
static Result<device> default_device();
```

### `supports_format`

Check if a nozzle format is supported by this device.

```cpp
bool supports_format(texture_format format, texture_usage usage) const;
```

---

## Discovery

```cpp
#include <nozzle/discovery.hpp>

std::vector<sender_info> enumerate_senders();
```

Returns all active senders on the local machine.

```cpp
auto senders = nozzle::enumerate_senders();
for (const auto &s : senders) {
    std::cout << s.name << " (" << s.application_name << ")\n";
}
```

---

## Pixel Access

```cpp
#include <nozzle/pixel_access.hpp>

struct mapped_pixels {
    void *data{nullptr};
    uint32_t row_bytes{0};
    uint32_t width{0};
    uint32_t height{0};
    texture_format format{texture_format::unknown};
};

Result<mapped_pixels> lock_frame_pixels(const frame &frm);
void unlock_frame_pixels(const frame &frm);

Result<mapped_pixels> lock_writable_pixels(writable_frame &frm);
void unlock_writable_pixels(writable_frame &frm);
```

### Reading pixels from a received frame:

```cpp
auto frame = receiver.acquire_frame({.timeout_ms = 1000}).value();
auto pixels = nozzle::lock_frame_pixels(frame).value();
auto *buf = static_cast<uint8_t *>(pixels.data);
// Read pixels: buf[y * pixels.row_bytes + x * bytes_per_pixel + channel]
nozzle::unlock_frame_pixels(frame);
```

### Writing pixels to a writable frame:

```cpp
auto frame = sender.acquire_writable_frame({
    .width = 512, .height = 512,
    .format = nozzle::texture_format::rgba8_unorm
}).value();
auto pixels = nozzle::lock_writable_pixels(frame).value();
auto *buf = static_cast<uint8_t *>(pixels.data);
// Write pixels...
nozzle::unlock_writable_pixels(frame);
sender.commit_frame(frame);
```

---

## OpenGL Interop

```cpp
#include <nozzle/backends/opengl.hpp>

namespace nozzle::gl {

struct gl_texture_desc {
    uint32_t name{0};           // GLuint
    uint32_t target{0x0DE1};    // GL_TEXTURE_2D
    uint32_t width{0};
    uint32_t height{0};
    texture_format format{texture_format::rgba8_unorm};
};

Result<void> publish_gl_texture(sender &snd, const gl_texture_desc &gl_desc);
Result<void> copy_frame_to_gl_texture(const frame &frm, const gl_texture_desc &gl_desc);

}
```

Requires an active GL context on the calling thread.

### Publish an existing OpenGL texture:

```cpp
nozzle::gl::gl_texture_desc gl_desc{
    .name = gl_tex_name,
    .target = GL_TEXTURE_2D,
    .width = 1920,
    .height = 1080,
    .format = nozzle::texture_format::bgra8_unorm
};
sender.publish_external_texture(...) // not needed
nozzle::gl::publish_gl_texture(sender, gl_desc).value();
```

### Copy a received frame to an OpenGL texture:

```cpp
auto frame = receiver.acquire_frame({.timeout_ms = 1000}).value();
nozzle::gl::copy_frame_to_gl_texture(frame, gl_desc).value();
```
