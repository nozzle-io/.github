#include <nozzle/nozzle_c.h>
#include <inttypes.h>
#include <stdio.h>

enum { image_width = 320, image_height = 240 };

static int check(NozzleErrorCode error, const char *operation) {
    if (error == NOZZLE_OK) return 1;
    fprintf(stderr, "%s failed: error %d\n", operation, (int)error);
    return 0;
}

static int supported_view(const NozzleMappedPixels *pixels) {
    const int64_t row_bytes = (int64_t)image_width * 4;
    const int64_t max_stride = (PTRDIFF_MAX - row_bytes) / (image_height - 1);
    const int64_t stride = pixels->row_stride_bytes;
    if (!pixels->data || pixels->width != image_width ||
        pixels->height != image_height ||
        pixels->format != NOZZLE_FORMAT_RGBA8_UNORM ||
        pixels->origin != NOZZLE_ORIGIN_TOP_LEFT ||
        (stride > -row_bytes && stride < row_bytes) ||
        stride < -max_stride || stride > max_stride) {
        fprintf(stderr, "Expected a 320x240 top-left RGBA8 view with usable signed stride\n");
        return 0;
    }
    return 1;
}

int main(void) {
    NozzleSender *sender = NULL;
    NozzleReceiver *receiver = NULL;
    NozzleFrame *writable = NULL;
    NozzleFrame *received = NULL;
    NozzlePixelMapping *mapping = NULL;
    NozzleMappedPixels pixels = {0};
    NozzleSenderDesc sender_desc = {0};
    NozzleReceiverDesc receiver_desc = {0};
    NozzleAcquireDesc acquire_desc = {0};
    int result = 1;

    sender_desc.name = "c_reference_output";
    sender_desc.application_name = "C reference example";
    sender_desc.ring_buffer_size = 3;
    sender_desc.fallback_flags_valid = 1;
    sender_desc.fallback_flags = NOZZLE_FALLBACK_NONE;
    if (!check(nozzle_sender_create(&sender_desc, &sender), "create sender"))
        goto cleanup;
    if (!check(nozzle_sender_acquire_writable_frame(
            sender, image_width, image_height, NOZZLE_FORMAT_RGBA8_UNORM,
            &writable), "acquire writable frame"))
        goto cleanup;
    if (!check(nozzle_frame_lock_writable_pixels_mapping_with_origin(
            writable, NOZZLE_ORIGIN_TOP_LEFT, &mapping, &pixels), "map write"))
        goto cleanup;
    if (!supported_view(&pixels)) goto cleanup;

    /* data is the requested-origin row; stride may be negative or padded. */
    for (uint32_t y = 0; y < pixels.height; ++y) {
        uint8_t *row = (uint8_t *)pixels.data +
            (ptrdiff_t)((int64_t)y * pixels.row_stride_bytes);
        for (uint32_t x = 0; x < pixels.width; ++x) {
            row[x * 4 + 0] = 255;
            row[x * 4 + 1] = y < pixels.height / 2 ? 128 : 0;
            row[x * 4 + 2] = 64;
            row[x * 4 + 3] = 255;
        }
    }

    /* Checked unlock consumes mapping even on backend failure. */
    if (!check(nozzle_pixel_mapping_unlock_checked(&mapping), "unmap write"))
        goto cleanup;
    if (!check(nozzle_sender_commit_frame(sender, writable), "commit frame"))
        goto cleanup;
    nozzle_frame_release(writable);
    writable = NULL;

    /* Same-process lifetime demonstration, not an inter-process smoke test. */
    receiver_desc.name = sender_desc.name;
    receiver_desc.application_name = "C reference receiver";
    receiver_desc.receive_mode = NOZZLE_RECEIVE_LATEST_ONLY;
    if (!check(nozzle_receiver_create(&receiver_desc, &receiver), "create receiver"))
        goto cleanup;
    acquire_desc.timeout_ms = 1000;
    if (!check(nozzle_receiver_acquire_frame(receiver, &acquire_desc, &received),
               "acquire received frame"))
        goto cleanup;
    if (!check(nozzle_frame_lock_pixels_mapping_with_origin(
            received, NOZZLE_ORIGIN_TOP_LEFT, &mapping, &pixels), "map read"))
        goto cleanup;
    if (!supported_view(&pixels)) goto cleanup;
    const uint8_t *first_pixel = (const uint8_t *)pixels.data;
    printf("Received %" PRIu32 "x%" PRIu32 ", stride=%" PRId64
           ", first RGBA=(%u,%u,%u,%u)\n",
           pixels.width, pixels.height, pixels.row_stride_bytes,
           (unsigned)first_pixel[0], (unsigned)first_pixel[1],
           (unsigned)first_pixel[2], (unsigned)first_pixel[3]);
    if (!check(nozzle_pixel_mapping_unlock_checked(&mapping), "unmap read"))
        goto cleanup;
    result = 0;

cleanup:
    if (mapping && !check(nozzle_pixel_mapping_unlock_checked(&mapping),
                          "cleanup mapping"))
        result = 1;
    if (writable) {
        /* A failed commit may already have consumed the reservation. */
        if (!check(nozzle_sender_discard_frame(sender, writable), "discard frame"))
            result = 1;
        nozzle_frame_release(writable);
    }
    if (received) nozzle_frame_release(received);
    if (receiver) nozzle_receiver_destroy(receiver);
    if (sender) nozzle_sender_destroy(sender);
    return result;
}
