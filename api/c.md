---
layout: default
title: C API
---

The C API supports plugin and host integration. Nozzle is currently pre-ABI-stable
v0.x: source and binary compatibility are not guaranteed across changes. All
types use the `Nozzle` prefix. Include:

```c
#include <nozzle/nozzle_c.h>
```

### Metadata Getter Migration

The borrowed getters `nozzle_sender_get_info` and
`nozzle_receiver_get_connected_info`, and the obsolete
`NozzleConnectedSenderInfo` type, have been removed. Use the owned snapshot
getters below with their corresponding complete output structs. This is a v0.x
source/ABI break: migrate callers and rebuild applications, plugins and bindings
against matching headers and core libraries. An old binary that imports a
removed symbol is not compatible with the new library. Discovery's
`NozzleSenderInfo` and enumeration/free APIs remain available.

These structs describe the native C ABI, not a serialized or shared-memory wire
layout. Use the matching header and target compiler's `sizeof`, alignment and
`offsetof`; do not assume one byte size or packed layout across platforms.
Current CI ABI verification targets macOS arm64 and Linux/Windows x86_64. This
is not an i386 SysV ABI guarantee. The universal macOS SDK also compiles x86_64;
that compilation is not x86_64 runtime evidence. Do not add packing to these
structs; the complete layout is governed by the matching native header.

---

## Error Handling

All functions return `NozzleErrorCode`. `NOZZLE_OK` (0) indicates success.

```c
typedef enum NozzleErrorCode {
    NOZZLE_OK = 0,
    NOZZLE_ERROR_UNKNOWN,
    NOZZLE_ERROR_INVALID_ARGUMENT,
    NOZZLE_ERROR_UNSUPPORTED_BACKEND,
    NOZZLE_ERROR_UNSUPPORTED_FORMAT,
    NOZZLE_ERROR_DEVICE_MISMATCH,
    NOZZLE_ERROR_RESOURCE_CREATION_FAILED,
    NOZZLE_ERROR_SHARED_HANDLE_FAILED,
    NOZZLE_ERROR_SENDER_NOT_FOUND,
    NOZZLE_ERROR_SENDER_CLOSED,
    NOZZLE_ERROR_TIMEOUT,
    NOZZLE_ERROR_BACKEND_ERROR,
} NozzleErrorCode;
```

---

## Opaque Types

```c
typedef struct NozzleSender NozzleSender;
typedef struct NozzleReceiver NozzleReceiver;
typedef struct NozzleFrame NozzleFrame;
typedef struct NozzleTexture NozzleTexture;
typedef struct NozzleDevice NozzleDevice;
```

---

## Enums

### NozzleBackendType

```c
typedef enum NozzleBackendType {
    NOZZLE_BACKEND_UNKNOWN = 0,
    NOZZLE_BACKEND_D3D11,
    NOZZLE_BACKEND_METAL,
    NOZZLE_BACKEND_OPENGL,
} NozzleBackendType;
```

### NozzleTextureFormat

```c
typedef enum NozzleTextureFormat {
    NOZZLE_FORMAT_UNKNOWN = 0,
    NOZZLE_FORMAT_R8_UNORM,
    NOZZLE_FORMAT_RG8_UNORM,
    NOZZLE_FORMAT_RGBA8_UNORM,
    NOZZLE_FORMAT_BGRA8_UNORM,
    NOZZLE_FORMAT_RGBA8_SRGB,
    NOZZLE_FORMAT_BGRA8_SRGB,
    NOZZLE_FORMAT_R16_UNORM,
    NOZZLE_FORMAT_RG16_UNORM,
    NOZZLE_FORMAT_RGBA16_UNORM,
    NOZZLE_FORMAT_R16_FLOAT,
    NOZZLE_FORMAT_RG16_FLOAT,
    NOZZLE_FORMAT_RGBA16_FLOAT,
    NOZZLE_FORMAT_R32_FLOAT,
    NOZZLE_FORMAT_RG32_FLOAT,
    NOZZLE_FORMAT_RGBA32_FLOAT,
    NOZZLE_FORMAT_R32_UINT,
    NOZZLE_FORMAT_RGBA32_UINT,
    NOZZLE_FORMAT_DEPTH32_FLOAT,
} NozzleTextureFormat;
```

### NozzleReceiveMode

```c
typedef enum NozzleReceiveMode {
    NOZZLE_RECEIVE_LATEST_ONLY = 0,
    NOZZLE_RECEIVE_SEQUENTIAL_BEST_EFFORT,
} NozzleReceiveMode;
```

### NozzleFrameStatus

```c
typedef enum NozzleFrameStatus {
    NOZZLE_FRAME_NEW = 0,
    NOZZLE_FRAME_NO_NEW,
    NOZZLE_FRAME_DROPPED,
    NOZZLE_FRAME_SENDER_CLOSED,
    NOZZLE_FRAME_ERROR,
} NozzleFrameStatus;
```

---

## Descriptor Structs

### NozzleSenderDesc

```c
typedef struct NozzleSenderDesc {
    const char *name;
    const char *application_name;
    uint32_t ring_buffer_size;
    int allow_format_fallback;
} NozzleSenderDesc;
```

| Field | Type | Description |
|-------|------|-------------|
| `name` | `const char *` | Sender name for discovery |
| `application_name` | `const char *` | Application name metadata |
| `ring_buffer_size` | `uint32_t` | Number of frames in ring buffer (default: 3) |
| `allow_format_fallback` | `int` | Allow format fallback (nonzero = true) |

### NozzleReceiverDesc

```c
typedef struct NozzleReceiverDesc {
    const char *name;
    const char *application_name;
    NozzleReceiveMode receive_mode;
} NozzleReceiverDesc;
```

### NozzleAcquireDesc

```c
typedef struct NozzleAcquireDesc {
    uint64_t timeout_ms;
} NozzleAcquireDesc;
```

### NozzleFrameInfo

```c
typedef struct NozzleFrameInfo {
    uint64_t frame_index;
    uint64_t timestamp_ns;
    uint32_t width;
    uint32_t height;
    NozzleTextureFormat format;
    uint32_t dropped_frame_count;
} NozzleFrameInfo;
```

---

## Sender API

### nozzle_sender_create

```c
NozzleErrorCode nozzle_sender_create(
    const NozzleSenderDesc *desc,
    NozzleSender **out_sender
);
```

| Parameter | Type | Description |
|-----------|------|-------------|
| `desc` | `const NozzleSenderDesc *` | Sender descriptor |
| `out_sender` | `NozzleSender **` | Receives the created sender handle |

**Returns:** `NOZZLE_OK` on success.

### nozzle_sender_destroy

```c
void nozzle_sender_destroy(NozzleSender *sender);
```

### nozzle_sender_publish_texture

```c
NozzleErrorCode nozzle_sender_publish_texture(
    NozzleSender *sender,
    NozzleTexture *texture
);
```

### nozzle_sender_acquire_writable_frame

```c
NozzleErrorCode nozzle_sender_acquire_writable_frame(
    NozzleSender *sender,
    uint32_t width,
    uint32_t height,
    NozzleTextureFormat format,
    NozzleFrame **out_frame
);
```

### nozzle_sender_commit_frame

```c
NozzleErrorCode nozzle_sender_commit_frame(
    NozzleSender *sender,
    NozzleFrame *frame
);
```

### nozzle_sender_get_info_snapshot

```c
#define NOZZLE_SENDER_NAME_CAPACITY 64
#define NOZZLE_APPLICATION_NAME_CAPACITY 64
#define NOZZLE_SENDER_ID_CAPACITY 37

typedef struct NozzleSenderInfoSnapshot {
    char name[NOZZLE_SENDER_NAME_CAPACITY];
    char application_name[NOZZLE_APPLICATION_NAME_CAPACITY];
    char id[NOZZLE_SENDER_ID_CAPACITY];
    NozzleBackendType backend;
} NozzleSenderInfoSnapshot;

NOZZLE_C_API NozzleErrorCode nozzle_sender_get_info_snapshot(
    NozzleSender *sender,
    NozzleSenderInfoSnapshot *out_info
);
```

Capacities include the trailing NUL: names and application names hold at most
63 UTF-8 bytes, not 63 characters; IDs hold a 36-byte ASCII UUID plus NUL.
Oversized sender names are rejected at creation; application names are truncated
at a UTF-8 code-point boundary.

Pass a valid sender and caller-owned storage for the complete struct. On
`NOZZLE_OK`, all strings are inline copies. The result remains valid after later
API calls or sender destruction, for as long as the caller's storage remains
alive. Copying the struct copies its string bytes. No nozzle free function is
needed for the snapshot, and its array members must not be freed individually.
This ownership does not make concurrent handle destruction safe.

---

## Receiver API

### nozzle_receiver_create

```c
NozzleErrorCode nozzle_receiver_create(
    const NozzleReceiverDesc *desc,
    NozzleReceiver **out_receiver
);
```

### nozzle_receiver_destroy

```c
void nozzle_receiver_destroy(NozzleReceiver *receiver);
```

### nozzle_receiver_acquire_frame

```c
NozzleErrorCode nozzle_receiver_acquire_frame(
    NozzleReceiver *receiver,
    const NozzleAcquireDesc *desc,
    NozzleFrame **out_frame
);
```

Pass `NULL` for `desc` to use non-blocking (timeout_ms = 0) behavior.

### nozzle_receiver_get_connected_info_snapshot

```c
typedef struct NozzleConnectedSenderSnapshot {
    char name[NOZZLE_SENDER_NAME_CAPACITY];
    char application_name[NOZZLE_APPLICATION_NAME_CAPACITY];
    char id[NOZZLE_SENDER_ID_CAPACITY];
    uint32_t connected;
    NozzleBackendType backend;
    uint32_t width;
    uint32_t height;
    NozzleTextureFormat format;
    NozzleTextureFormat semantic_format;
    double estimated_fps;
    uint64_t frame_counter;
    uint64_t last_update_time_ns;
    NozzleNativeFormatKind native_format_kind;
    uint32_t native_format_value;
    uint64_t native_format_modifier;
} NozzleConnectedSenderSnapshot;

NOZZLE_C_API NozzleErrorCode nozzle_receiver_get_connected_info_snapshot(
    NozzleReceiver *receiver,
    NozzleConnectedSenderSnapshot *out_info
);
```

Pass a valid receiver and caller-owned storage for the complete struct, including
the native-format tail. It uses the same capacities and inline-copy lifetime as
the sender snapshot: no borrowed string pointers and no nozzle free operation.
Returned copies survive later getters, sender transitions and receiver destruction.

The connection flag and metadata are copied together under the same receiver
lock. `connected` is 1 when the receiver last observed a connection and 0 after
it observed a disconnect. After an acquire reports `NOZZLE_ERROR_SENDER_CLOSED`,
the snapshot retains the last-known sender identity with `connected == 0`.
`NOZZLE_OK` means the snapshot call succeeded, not that the receiver is connected.

A zero-initialized/default snapshot has `connected == 0` and empty identity
arrays, representing no successful connection yet. That value is not evidence
of a successful getter call for an unavailable sender: the current C receiver
factory requires an initial connection. If creation fails, it returns an error
and leaves the output handle null; do not call the getter on that null handle.

This is last-observed state, not an active liveness probe or a reconnect operation.
Sender exit alone need not update the flag until the receiver observes it, and
the sender may exit immediately after a snapshot returns. Keep the receiver
handle valid during the call; owned output does not permit racing handle destruction.

---

## Frame API

### nozzle_frame_get_info

```c
NozzleErrorCode nozzle_frame_get_info(
    NozzleFrame *frame,
    NozzleFrameInfo *out_info
);
```

### nozzle_frame_release

```c
void nozzle_frame_release(NozzleFrame *frame);
```

---

## Discovery

### nozzle_enumerate_senders

```c
typedef struct NozzleSenderInfo {
    const char *name;
    const char *application_name;
    const char *id;
    NozzleBackendType backend;
} NozzleSenderInfo;

typedef struct NozzleSenderInfoArray {
    NozzleSenderInfo *items;
    uint32_t count;
} NozzleSenderInfoArray;

NozzleErrorCode nozzle_enumerate_senders(
    NozzleSenderInfoArray *out_array
);
```

### nozzle_free_sender_info_array

```c
void nozzle_free_sender_info_array(NozzleSenderInfoArray *array);
```

Must be called to free the allocation returned by `nozzle_enumerate_senders`.
Discovery is distinct from the inline snapshots: each item's string pointers
borrow storage owned by that returned array and remain valid only until
`nozzle_free_sender_info_array` is called. Copying a `NozzleSenderInfo` item does
not copy its strings. Copy any strings needed afterward before freeing the array;
do not free items or strings individually, and do not use the array-free function
on a snapshot.

```c
NozzleSenderInfoArray arr;
if (nozzle_enumerate_senders(&arr) == NOZZLE_OK) {
    for (uint32_t i = 0; i < arr.count; i++) {
        printf("Sender: %s\n", arr.items[i].name);
    }
    nozzle_free_sender_info_array(&arr);
}
```

---

## Device API

### nozzle_device_get_default

```c
NozzleErrorCode nozzle_device_get_default(
    NozzleDevice **out_device
);
```

### nozzle_device_destroy

```c
void nozzle_device_destroy(NozzleDevice *device);
```

---

## Pixel Access (CPU)

### NozzleMappedPixels

```c
typedef struct NozzleMappedPixels {
    void *data;
    uint32_t row_bytes;
    uint32_t width;
    uint32_t height;
    NozzleTextureFormat format;
} NozzleMappedPixels;
```

### nozzle_frame_lock_pixels

```c
NozzleErrorCode nozzle_frame_lock_pixels(
    NozzleFrame *frame,
    NozzleMappedPixels *out_pixels
);
```

### nozzle_frame_unlock_pixels

```c
void nozzle_frame_unlock_pixels(NozzleFrame *frame);
```

### nozzle_frame_lock_writable_pixels

```c
NozzleErrorCode nozzle_frame_lock_writable_pixels(
    NozzleFrame *frame,
    NozzleMappedPixels *out_pixels
);
```

### nozzle_frame_unlock_writable_pixels

```c
void nozzle_frame_unlock_writable_pixels(NozzleFrame *frame);
```

---

## GL Interop

### nozzle_sender_publish_gl_texture

```c
NozzleErrorCode nozzle_sender_publish_gl_texture(
    NozzleSender *sender,
    uint32_t gl_texture_name,
    uint32_t gl_target,
    uint32_t width,
    uint32_t height,
    NozzleTextureFormat format
);
```

Requires an active GL context on the calling thread.

### nozzle_frame_copy_to_gl_texture

```c
NozzleErrorCode nozzle_frame_copy_to_gl_texture(
    NozzleFrame *frame,
    uint32_t gl_texture_name,
    uint32_t gl_target,
    uint32_t width,
    uint32_t height,
    NozzleTextureFormat format
);
```

---

## Full Example

```c
#include <nozzle/nozzle_c.h>
#include <stdio.h>
#include <string.h>

int main() {
    // Create sender
    NozzleSender *sender;
    NozzleSenderDesc desc = {0};
    desc.name = "my_output";
    desc.application_name = "MyApp";
    desc.ring_buffer_size = 3;

    if (nozzle_sender_create(&desc, &sender) != NOZZLE_OK) {
        fprintf(stderr, "Failed to create sender\n");
        return 1;
    }

    // Acquire writable frame
    NozzleFrame *frame;
    if (nozzle_sender_acquire_writable_frame(
            sender, 1920, 1080,
            NOZZLE_FORMAT_RGBA8_UNORM, &frame) != NOZZLE_OK) {
        fprintf(stderr, "Failed to acquire frame\n");
        nozzle_sender_destroy(sender);
        return 1;
    }

    // Write pixels
    NozzleMappedPixels pixels;
    if (nozzle_frame_lock_writable_pixels(frame, &pixels) == NOZZLE_OK) {
        uint8_t *buf = (uint8_t *)pixels.data;
        for (uint32_t i = 0; i < pixels.width * pixels.height; i++) {
            buf[i * 4 + 0] = 255;
            buf[i * 4 + 1] = 128;
            buf[i * 4 + 2] = 64;
            buf[i * 4 + 3] = 255;
        }
        nozzle_frame_unlock_writable_pixels(frame);
    }

    // Commit
    nozzle_sender_commit_frame(sender, frame);
    nozzle_frame_release(frame);

    // Create receiver in another process
    NozzleReceiver *receiver;
    NozzleReceiverDesc recv_desc = {0};
    recv_desc.name = "my_output";
    recv_desc.application_name = "MyViewer";

    if (nozzle_receiver_create(&recv_desc, &receiver) != NOZZLE_OK) {
        fprintf(stderr, "Failed to create receiver\n");
        nozzle_sender_destroy(sender);
        return 1;
    }

    // Acquire frame
    NozzleAcquireDesc acq = { .timeout_ms = 1000 };
    NozzleFrame *recv_frame;
    if (nozzle_receiver_acquire_frame(receiver, &acq, &recv_frame) == NOZZLE_OK) {
        NozzleFrameInfo info;
        nozzle_frame_get_info(recv_frame, &info);
        printf("Received frame: %ux%u\n", info.width, info.height);
        nozzle_frame_release(recv_frame);
    }

    nozzle_receiver_destroy(receiver);
    nozzle_sender_destroy(sender);
    return 0;
}
```
