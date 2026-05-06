---
layout: default
title: Go (nozzle.go)
---

[nozzle.go](https://github.com/nozzle-io/nozzle.go) provides Go bindings for nozzle via cgo.

## Setup

```bash
git clone --recursive https://github.com/nozzle-io/nozzle.go.git
cd nozzle.go
make
```

## Requirements

- Go 1.21+
- C++17 compiler (clang / MSVC)
- macOS 12+ / Windows 10+ / Linux

## Sender

```go
sender, err := nozzle.NewSender(nozzle.SenderDesc{
    Name:            "my_sender",
    ApplicationName: "MyApp",
    RingBufferSize:  3,
})
if err != nil {
    panic(err)
}
defer sender.Close()

frame, err := sender.AcquireWritableFrame(1920, 1080, nozzle.FormatRGBA8UNorm)
pixels, err := frame.LockWritablePixels(nozzle.OriginTopLeft)
defer frame.UnmapWritablePixels()
for y := 0; y < pixels.Height; y++ {
    row, _ := pixels.Row(y)
    for i := range row {
        row[i] = 0xFF
    }
}
sender.CommitFrame(frame)
```

## Receiver

```go
receiver, err := nozzle.NewReceiver(nozzle.ReceiverDesc{
    Name:            "my_sender",
    ApplicationName: "MyViewer",
    ReceiveMode:     nozzle.ReceiveLatestOnly,
})
if err != nil {
    panic(err)
}
defer receiver.Close()

frame, err := receiver.AcquireFrame(5000)
if err != nil {
    panic(err)
}
defer frame.Release()

info, _ := frame.Info()
fmt.Printf("%dx%d frame #%d\n", info.Width, info.Height, info.FrameIndex)
```

## Error Handling

All fallible operations return `error`. Nozzle errors implement the `error` interface:

```go
_, err := nozzle.NewSender(nozzle.SenderDesc{Name: ""})
if err == nozzle.ErrorInvalidArgument {
    // handle bad args
}
```

## Platform Notes

- **macOS**: Links Metal, IOSurface, Foundation, Accelerate, OpenGL via cgo
- **Windows**: Links d3d11, dxgi, opengl32, bcrypt via cgo
- **Linux**: Links drm, gbm, EGL, GL via cgo
