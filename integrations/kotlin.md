---
layout: default
title: Kotlin (nozzle.kotlin)
---

[nozzle.kotlin](https://github.com/nozzle-io/nozzle.kotlin) provides Kotlin/JVM JNI bindings for nozzle.

## Setup

```bash
git clone --recursive https://github.com/nozzle-io/nozzle.kotlin.git
cd nozzle.kotlin
make
./gradlew build
```

## Requirements

- JDK 11+
- C++17 compiler (clang / MSVC)
- macOS 12+ / Windows 10+ / Linux

## Sender

```kotlin
Sender(SenderDesc("kotlin-sender", "MyApp", ringBufferSize = 3)).use { sender ->
    sender.acquireWritableFrame(1920, 1080, TextureFormat.Rgba8Unorm).use { frame ->
        val pixels = frame.lockWritablePixels(TextureOrigin.TopLeft)
        for (y in 0 until pixels.height) {
            val row = pixels.row(y)
            row.fill(0xFF.toByte())
        }
        pixels.unmap()
        sender.commitFrame(frame)
    }
}
```

## Receiver

```kotlin
Receiver(ReceiverDesc("kotlin-sender", "MyViewer")).use { receiver ->
    receiver.acquireFrame(5000).use { frame ->
        val info = frame.info()
        println("${info.width}x${info.height} frame #${info.frameIndex}")
    }
}
```

## Error Handling

All fallible operations throw `NozzleException` with an `errorCode`:

```kotlin
try {
    Sender(SenderDesc("", "test"))
} catch (e: NozzleException) {
    if (e.errorCode == ErrorCode.InvalidArgument) {
        // handle bad args
    }
}
```

## Platform Notes

- **macOS**: Links Metal, IOSurface, Foundation, Accelerate, OpenGL via JNI
- **Windows**: Links d3d11, dxgi, opengl32, bcrypt via JNI
- **Linux**: Links drm, gbm, EGL, GL via JNI
