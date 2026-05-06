---
layout: default
title: Java (nozzle.java)
---

[nozzle.java](https://github.com/nozzle-io/nozzle.java) provides Java JNI bindings for nozzle.

## Setup

```bash
git clone --recursive https://github.com/nozzle-io/nozzle.java.git
cd nozzle.java
make
./gradlew build
```

## Requirements

- Java 11+
- C++17 compiler (clang / MSVC)
- macOS 12+ / Windows 10+ / Linux

## Sender

```java
try (Sender sender = Sender.create(new SenderDesc("java-sender", "MyApp", 3))) {
    try (WritableFrame frame = sender.acquireWritableFrame(1920, 1080, TextureFormat.RGBA8_UNORM)) {
        MappedPixels pixels = frame.lockWritablePixels(TextureOrigin.TOP_LEFT);
        for (int y = 0; y < pixels.getHeight(); y++) {
            byte[] row = pixels.row(y);
            Arrays.fill(row, (byte) 0xFF);
        }
        pixels.unmap();
        sender.commitFrame(frame);
    }
}
```

## Receiver

```java
try (Receiver receiver = Receiver.create(new ReceiverDesc("java-sender", "MyViewer"))) {
    try (Frame frame = receiver.acquireFrame(5000)) {
        FrameInfo info = frame.getInfo();
        System.out.printf("%dx%d frame #%d%n", info.getWidth(), info.getHeight(), info.getFrameIndex());
    }
}
```

## Error Handling

All fallible operations throw `NozzleException` with an `ErrorCode`:

```java
try {
    Sender.create(new SenderDesc("", "test"));
} catch (NozzleException e) {
    if (e.getErrorCode() == ErrorCode.INVALID_ARGUMENT) {
        // handle bad args
    }
}
```

## Platform Notes

- **macOS**: Links Metal, IOSurface, Foundation, Accelerate, OpenGL via JNI
- **Windows**: Links d3d11, dxgi, opengl32, bcrypt via JNI
- **Linux**: Links drm, gbm, EGL, GL via JNI
