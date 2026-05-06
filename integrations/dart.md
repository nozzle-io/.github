---
layout: default
title: Dart (nozzle.dart)
---

[nozzle.dart](https://github.com/nozzle-io/nozzle.dart) provides Dart FFI bindings for nozzle.

## Setup

```bash
git clone --recursive https://github.com/nozzle-io/nozzle.dart.git
cd nozzle.dart
make
dart pub get
```

## Requirements

- Dart SDK 3.3+
- C++17 compiler (clang / MSVC)
- macOS 12+ / Windows 10+ / Linux

## Sender

```dart
final sender = Sender.create(const SenderDesc(
  name: 'dart-sender',
  applicationName: 'MyApp',
  ringBufferSize: 3,
));
sender.close();

final frame = sender.acquireWritableFrame(1920, 1080, TextureFormat.rgba8Unorm);
final pixels = frame.lockWritablePixels(TextureOrigin.topLeft);
for (var y = 0; y < pixels.height; y++) {
  final row = pixels.row(y);
  for (var i = 0; i < row.length; i++) {
    row[i] = 0xFF;
  }
}
pixels.unmap();
sender.commitFrame(frame);
```

## Receiver

```dart
final receiver = Receiver.create(const ReceiverDesc(
  name: 'dart-sender',
  applicationName: 'MyViewer',
  receiveMode: ReceiveMode.latestOnly,
));
receiver.close();

final frame = receiver.acquireFrame(timeoutMs: 5000);
final info = frame.info();
print('${info.width}x${info.height} frame #${info.frameIndex}');
frame.release();
```

## Error Handling

All fallible operations throw `NozzleException` with a descriptive `ErrorCode`:

```dart
try {
  final frame = sender.acquireWritableFrame(0, 0, TextureFormat.unknown);
} on NozzleException catch (e) {
  if (e.code == ErrorCode.invalidArgument) {
    // handle bad args
  }
}
```

## Platform Notes

- **macOS**: Links Metal, IOSurface, Foundation, Accelerate, OpenGL automatically
- **Windows**: Links d3d11, dxgi, opengl32, bcrypt automatically
- **Linux**: Links drm, gbm, EGL, GL automatically
