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

This is a curated reference, not the complete API. Declarations below target
[the canonical header at core `{{ site.data.c_reference.core_revision }}`](https://github.com/nozzle-io/nozzle/blob/{{ site.data.c_reference.core_revision }}/include/nozzle/nozzle_c.h).
The matching header is authoritative: include it rather than redeclaring these
types or adding packing. Build against the same core revision as your library.

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

Functions declared with return type `NozzleErrorCode` report `NOZZLE_OK` (0) on
success. Check their results before using output values. Some cleanup functions
return `void`; availability helpers in the canonical header return `int`.

```c
typedef enum NozzleErrorCode {
    NOZZLE_OK = 0,
    NOZZLE_ERROR_UNKNOWN = 1,
    NOZZLE_ERROR_INVALID_ARGUMENT = 2,
    NOZZLE_ERROR_UNSUPPORTED_BACKEND = 3,
    NOZZLE_ERROR_UNSUPPORTED_FORMAT = 4,
    NOZZLE_ERROR_DEVICE_MISMATCH = 5,
    NOZZLE_ERROR_RESOURCE_CREATION_FAILED = 6,
    NOZZLE_ERROR_SHARED_HANDLE_FAILED = 7,
    NOZZLE_ERROR_SENDER_NOT_FOUND = 8,
    NOZZLE_ERROR_SENDER_CLOSED = 9,
    NOZZLE_ERROR_TIMEOUT = 10,
    NOZZLE_ERROR_BACKEND_ERROR = 11,
    NOZZLE_ERROR_COMMAND_FAILED = 12,
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
typedef struct NozzlePixelMapping NozzlePixelMapping;
```

---

## Enums

### NozzleBackendType

```c
typedef enum NozzleBackendType {
    NOZZLE_BACKEND_UNKNOWN = 0,
    NOZZLE_BACKEND_D3D11 = 1,
    NOZZLE_BACKEND_METAL = 2,
    NOZZLE_BACKEND_OPENGL = 3,
    NOZZLE_BACKEND_DMA_BUF = 4,
} NozzleBackendType;
```

### NozzleTextureFormat

```c
typedef enum NozzleTextureFormat {
    NOZZLE_FORMAT_UNKNOWN = 0,
    NOZZLE_FORMAT_R8_UNORM = 1,
    NOZZLE_FORMAT_RG8_UNORM = 2,
    NOZZLE_FORMAT_RGB8_UNORM = 3,
    NOZZLE_FORMAT_RGBA8_UNORM = 4,
    NOZZLE_FORMAT_BGRA8_UNORM = 5,
    NOZZLE_FORMAT_RGBA8_SRGB = 6,
    NOZZLE_FORMAT_BGRA8_SRGB = 7,
    NOZZLE_FORMAT_R16_UNORM = 8,
    NOZZLE_FORMAT_RG16_UNORM = 9,
    NOZZLE_FORMAT_RGB16_UNORM = 10,
    NOZZLE_FORMAT_RGBA16_UNORM = 11,
    NOZZLE_FORMAT_R16_FLOAT = 12,
    NOZZLE_FORMAT_RG16_FLOAT = 13,
    NOZZLE_FORMAT_RGB16_FLOAT = 14,
    NOZZLE_FORMAT_RGBA16_FLOAT = 15,
    NOZZLE_FORMAT_R32_FLOAT = 16,
    NOZZLE_FORMAT_RG32_FLOAT = 17,
    NOZZLE_FORMAT_RGB32_FLOAT = 18,
    NOZZLE_FORMAT_RGBA32_FLOAT = 19,
    NOZZLE_FORMAT_R32_UINT = 20,
    NOZZLE_FORMAT_RGBA32_UINT = 21,
    NOZZLE_FORMAT_RGB32_UINT = 22,
    NOZZLE_FORMAT_DEPTH32_FLOAT = 23,
} NozzleTextureFormat;
```

### NozzleReceiveMode

```c
typedef enum NozzleReceiveMode {
    NOZZLE_RECEIVE_LATEST_ONLY = 0,
    NOZZLE_RECEIVE_SEQUENTIAL_BEST_EFFORT = 1,
} NozzleReceiveMode;
```

### NozzleFrameStatus

```c
typedef enum NozzleFrameStatus {
    NOZZLE_FRAME_NEW = 0,
    NOZZLE_FRAME_NO_NEW = 1,
    NOZZLE_FRAME_DROPPED = 2,
    NOZZLE_FRAME_SENDER_CLOSED = 3,
    NOZZLE_FRAME_ERROR = 4,
} NozzleFrameStatus;
```

`nozzle_receiver_acquire_frame` returns `NozzleErrorCode`, not `NozzleFrameStatus`.

### NozzleTextureOrigin

```c
typedef enum NozzleTextureOrigin {
    NOZZLE_ORIGIN_TOP_LEFT = 0,
    NOZZLE_ORIGIN_BOTTOM_LEFT = 1,
} NozzleTextureOrigin;
```

### NozzleTransferMode

```c
typedef enum NozzleTransferMode {
    NOZZLE_TRANSFER_UNKNOWN = 0,
    NOZZLE_TRANSFER_ZERO_COPY_SHARED_TEXTURE = 1,
    NOZZLE_TRANSFER_GPU_COPY = 2,
    NOZZLE_TRANSFER_CPU_COPY = 3,
} NozzleTransferMode;
```

### NozzleSyncMode

```c
typedef enum NozzleSyncMode {
    NOZZLE_SYNC_NONE = 0,
    NOZZLE_SYNC_ACCESS_GUARDED = 1,
    NOZZLE_SYNC_GPU_FENCE_BEST_EFFORT = 2,
} NozzleSyncMode;
```

### NozzleNativeFormatKind

```c
typedef enum NozzleNativeFormatKind {
    NOZZLE_NATIVE_KIND_UNKNOWN = 0,
    NOZZLE_NATIVE_KIND_MTL_PIXEL_FORMAT = 1,
    NOZZLE_NATIVE_KIND_DXGI_FORMAT = 2,
    NOZZLE_NATIVE_KIND_DRM_FOURCC = 3,
    NOZZLE_NATIVE_KIND_GL_INTERNAL_FORMAT = 4,
} NozzleNativeFormatKind;
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
    uint32_t fallback_flags;
    int fallback_flags_valid;
} NozzleSenderDesc;
```

| Field | Type | Description |
|-------|------|-------------|
| `name` | `const char *` | NUL-terminated valid UTF-8 identity, 1 to 63 bytes; never truncated |
| `application_name` | `const char *` | Valid UTF-8 display text, truncated to 63 bytes at a code-point boundary; NULL/empty becomes `unknown` |
| `ring_buffer_size` | `uint32_t` | Clamped to 1 through 8 slots in this revision; zero selects 1, not 3. Set 3 explicitly for a three-slot ring |
| `allow_format_fallback` | `int` | Deprecated compatibility field, used only when `fallback_flags_valid == 0` |
| `fallback_flags` | `uint32_t` | Explicit mask when `fallback_flags_valid != 0` |
| `fallback_flags_valid` | `int` | Nonzero selects the explicit mask, including an explicit zero mask |

```c
#define NOZZLE_FALLBACK_NONE               0u
#define NOZZLE_FALLBACK_STORAGE_COMPATIBLE (1u << 0)
#define NOZZLE_FALLBACK_CHANNEL_EXPANSION  (1u << 1)
#define NOZZLE_FALLBACK_QUALITY_LOSS       (1u << 2)
#define NOZZLE_FALLBACK_SAFE_DEFAULTS      (NOZZLE_FALLBACK_STORAGE_COMPATIBLE | NOZZLE_FALLBACK_CHANNEL_EXPANSION)

NOZZLE_C_API NozzleErrorCode nozzle_resolve_fallback_flags(
    const NozzleSenderDesc *desc,
    uint32_t *out_flags
);
```

This backend-independent helper resolves the same policy used by creation:

- `fallback_flags_valid != 0`: use `fallback_flags`; unknown bits are `NOZZLE_ERROR_INVALID_ARGUMENT`.
- Otherwise, `allow_format_fallback != 0`: enable safe defaults **and quality loss**.
- Otherwise: `NOZZLE_FALLBACK_NONE`, including a zero-initialized descriptor.

On failure, the helper leaves `*out_flags` unchanged. For explicit safe defaults,
set `fallback_flags_valid = 1` and `fallback_flags = NOZZLE_FALLBACK_SAFE_DEFAULTS`.

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
    NozzleTextureFormat semantic_format;
    NozzleTransferMode transfer_mode;
    NozzleSyncMode sync_mode;
    uint32_t dropped_frame_count;
} NozzleFrameInfo;
```

---

## Sender API

### nozzle_sender_create

```c
NOZZLE_C_API NozzleErrorCode nozzle_sender_create(
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
NOZZLE_C_API void nozzle_sender_destroy(NozzleSender *sender);
```

### nozzle_sender_publish_texture

```c
NOZZLE_C_API NozzleErrorCode nozzle_sender_publish_texture(
    NozzleSender *sender,
    NozzleTexture *texture
);
```

### nozzle_sender_acquire_writable_frame

```c
NOZZLE_C_API NozzleErrorCode nozzle_sender_acquire_writable_frame(
    NozzleSender *sender,
    uint32_t width,
    uint32_t height,
    NozzleTextureFormat format,
    NozzleFrame **out_frame
);
```

### nozzle_sender_commit_frame

```c
NOZZLE_C_API NozzleErrorCode nozzle_sender_commit_frame(
    NozzleSender *sender,
    NozzleFrame *frame
);
```

Commit only a writable frame acquired from this sender, after all CPU mappings
have been unlocked successfully. On success the reserved slot is returned to
the sender, but the caller still owns the `NozzleFrame` wrapper and must release
it. Check the return code; a failed commit is not a successful publication and
does not guarantee that the frame is reusable.

On Metal, GPU writes must have completed successfully **before** commit;
submission or `waitUntilScheduled` alone is insufficient. Commit/acquisition do
not submit or wait for a Metal command buffer, and ring rotation is not an
acknowledgment of receiver GPU completion.

### nozzle_sender_discard_frame

```c
NOZZLE_C_API NozzleErrorCode nozzle_sender_discard_frame(
    NozzleSender *sender,
    NozzleFrame *frame
);
```

Discard a writable reservation from this sender that should not be published.
Finish its CPU mapping first. On success the slot is returned without publishing;
the caller must still release the frame wrapper. Check discard's result too.
If commit failed, cleanup may find that the reservation has already been consumed;
do not treat a later discard error as publication success or reuse the frame.

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
NOZZLE_C_API NozzleErrorCode nozzle_receiver_create(
    const NozzleReceiverDesc *desc,
    NozzleReceiver **out_receiver
);
```

### nozzle_receiver_destroy

```c
NOZZLE_C_API void nozzle_receiver_destroy(NozzleReceiver *receiver);
```

### nozzle_receiver_acquire_frame

```c
NOZZLE_C_API NozzleErrorCode nozzle_receiver_acquire_frame(
    NozzleReceiver *receiver,
    const NozzleAcquireDesc *desc,
    NozzleFrame **out_frame
);
```

Pass `NULL` for `desc` to use the default `timeout_ms = 0`: no CPU-side wait for
a new publication. D3D11 also uses a zero-timeout synchronization attempt; other
backend synchronization/import work is not a universal nonblocking guarantee.
On success, release the returned frame with `nozzle_frame_release`.

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
NOZZLE_C_API NozzleErrorCode nozzle_frame_get_info(
    NozzleFrame *frame,
    NozzleFrameInfo *out_info
);
```

### nozzle_frame_release

```c
NOZZLE_C_API void nozzle_frame_release(NozzleFrame *frame);
```

Releases the wrapper, not an implicit commit or discard. Explicitly commit or
discard writable reservations before release. D3D11 abandoned reservations can
be reclaimed after their last active CPU mapping completes; release alone does
not return the reserved slot on other backends. A separately owned pixel-mapping
handle still requires its own unlock.

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

NOZZLE_C_API NozzleErrorCode nozzle_enumerate_senders(
    NozzleSenderInfoArray *out_array
);
```

### nozzle_free_sender_info_array

```c
NOZZLE_C_API void nozzle_free_sender_info_array(NozzleSenderInfoArray *array);
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
NOZZLE_C_API NozzleErrorCode nozzle_device_get_default(
    NozzleDevice **out_device
);
```

### nozzle_device_destroy

```c
NOZZLE_C_API void nozzle_device_destroy(NozzleDevice *device);
```

---

## Pixel Access (CPU)

### NozzleMappedPixels

```c
typedef struct NozzleMappedPixels {
    void *data;
    int64_t row_stride_bytes;
    uint32_t width;
    uint32_t height;
    NozzleTextureFormat format;
    NozzleTextureOrigin origin;
} NozzleMappedPixels;
```

The view borrows storage from its mapping. Copying this struct does not extend
the storage lifetime. A read mapping is read-only even though `data` is `void *`.
Use the returned `format`, dimensions, origin and **signed** stride; do not assume
packed RGBA8 or that the requested texture format is the mapped storage format.
Row `y` is at `(uint8_t *)data + (int64_t)y * row_stride_bytes`, starting from the
returned origin. Rows may contain padding; bottom-left mappings can use a
negative stride. Do not convert that stride to an unsigned byte count.

### Preferred Mapping Handles

```c
NOZZLE_C_API NozzleErrorCode nozzle_frame_lock_pixels_mapping_with_origin(
    NozzleFrame *frame,
    NozzleTextureOrigin desired_origin,
    NozzlePixelMapping **out_mapping,
    NozzleMappedPixels *out_pixels
);

NOZZLE_C_API NozzleErrorCode nozzle_frame_lock_writable_pixels_mapping_with_origin(
    NozzleFrame *frame,
    NozzleTextureOrigin desired_origin,
    NozzlePixelMapping **out_mapping,
    NozzleMappedPixels *out_pixels
);

NOZZLE_C_API NozzleErrorCode nozzle_pixel_mapping_unlock_checked(NozzlePixelMapping **mapping);
NOZZLE_C_API void nozzle_pixel_mapping_unlock(NozzlePixelMapping **mapping);
```

On successful lock, the returned `NozzlePixelMapping` owns backend cleanup and
the pixel view remains valid until that handle is unlocked. Writable locking
requires a writable frame acquired from the sender. Unlock each handle with the
mapping API, not the legacy frame-level unlock functions.

Use `nozzle_pixel_mapping_unlock_checked(&mapping)` to observe cleanup/upload
errors. For a valid handle, it consumes the mapping and sets the pointer to
`NULL` **even if backend cleanup fails**; the pixel view must no longer be used.
A null pointer or null handle is `NOZZLE_ERROR_INVALID_ARGUMENT`. The `void`
variant tolerates null and discards errors, so it cannot establish successful
write completion. Finish all CPU mappings and check their unlock results before
commit; do not publish after a failed writable unlock. Discard and release the
writable frame instead, checking discard's result as described above.

### Legacy Frame-Level Mapping

These compatibility APIs use one active compatibility mapping slot per frame.
Prefer the handle APIs above for new code. The old names without `_with_origin`
(`nozzle_frame_lock_pixels` and `nozzle_frame_lock_writable_pixels`) are not
declared APIs in this revision.

```c
NOZZLE_C_API NozzleErrorCode nozzle_frame_lock_pixels_with_origin(
    NozzleFrame *frame,
    NozzleTextureOrigin desired_origin,
    NozzleMappedPixels *out_pixels
);
NOZZLE_C_API void nozzle_frame_unlock_pixels(NozzleFrame *frame);

NOZZLE_C_API NozzleErrorCode nozzle_frame_lock_writable_pixels_with_origin(
    NozzleFrame *frame,
    NozzleTextureOrigin desired_origin,
    NozzleMappedPixels *out_pixels
);
NOZZLE_C_API NozzleErrorCode nozzle_frame_unlock_writable_pixels_checked(NozzleFrame *frame);
NOZZLE_C_API void nozzle_frame_unlock_writable_pixels(NozzleFrame *frame);
```

The read unlock is a no-op when no legacy read mapping is active. The checked
writable unlock returns `NOZZLE_ERROR_INVALID_ARGUMENT` when no legacy writable
mapping is active. Its `void` counterpart discards the result; use the checked
variant when write completion matters.

---

## GL Interop

### nozzle_sender_publish_gl_texture

```c
NOZZLE_C_API NozzleErrorCode nozzle_sender_publish_gl_texture(
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
NOZZLE_C_API NozzleErrorCode nozzle_frame_copy_to_gl_texture(
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

This single-process example publishes one asymmetric RGBA8 frame and reads it
while the sender remains alive. It demonstrates API use and cleanup, not a
long-running sender or a cross-process smoke test. It deliberately rejects
unexpected formats, dimensions or origins instead of guessing a conversion.
Run only on a machine with a supported native backend and CPU mapping support;
unsupported operations return a nonzero exit status, not a successful skip.

The [canonical C source](https://github.com/nozzle-io/.github/blob/main/_includes/examples/c_reference.c)
below is included directly into this page and compiled as C11 by the
[C Reference workflow](https://github.com/nozzle-io/.github/actions/workflows/c-reference.yml).
CI builds and installs the exact core revision cited above, then links this
source through `nozzle::nozzle` using the installed SDK. It does **not** execute
the example or verify pixels, GPU runtime, or inter-process transfer. It does not
compile every declaration excerpt on this page; those remain a source-review
responsibility when updating the pinned revision.

```c
{% include examples/c_reference.c %}
```

To compile against an installed SDK built from the cited revision, from a
checkout of this documentation repository:

```sh
cmake -S examples -B build/c-reference -DCMAKE_PREFIX_PATH=/absolute/path/to/nozzle-sdk
cmake --build build/c-reference
```
