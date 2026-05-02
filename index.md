---
layout: default
title: nozzle
---

<div class="hero">
  <h1>nozzle</h1>
  <p class="hero-subtitle">Cross-platform GPU texture sharing between local processes. Zero-copy on macOS, Windows, and Linux.</p>
  <p class="hero-platforms">macOS 12+ (Metal/IOSurface) &middot; Windows 10+ (D3D11) &middot; Linux (DMA-BUF)</p>
  <div class="hero-actions">
    <a href="getting-started.html" class="btn-primary">Get Started</a>
    <a href="api/cpp.html" class="btn-secondary">API Reference</a>
    <a href="https://github.com/nozzle-io/nozzle" class="btn-secondary">GitHub &rarr;</a>
  </div>
</div>

<div class="features">
  <div class="feature-card">
    <h3>Cross-Platform</h3>
    <p>Metal/IOSurface on macOS, D3D11 on Windows, DMA-BUF on Linux. Same API, every platform.</p>
  </div>
  <div class="feature-card">
    <h3>Zero Dependencies</h3>
    <p>C++17 STL + OS frameworks only. Static library links into any project without runtime deps.</p>
  </div>
  <div class="feature-card">
    <h3>Modern C++ API</h3>
    <p><code>Result&lt;T&gt;</code> error handling, no exceptions, no RTTI. Clean snake_case throughout.</p>
  </div>
  <div class="feature-card">
    <h3>C ABI</h3>
    <p>Full C API for plugin/host integration. Bindings for Python, Rust, Swift, and more.</p>
  </div>
  <div class="feature-card">
    <h3>High-Precision Formats</h3>
    <p>R16F, RGBA16F, R32F, RGBA32F, and more. Not limited to 8-bit color.</p>
  </div>
  <div class="feature-card">
    <h3>Thread-Safe</h3>
    <p>Same sender/receiver callable from multiple threads. Object-level thread safety.</p>
  </div>
</div>

<h2>Quick Example</h2>

<p>Share a texture between two processes in a few lines:</p>

<div style="display: grid; grid-template-columns: 1fr 1fr; gap: 16px;">
<div>

<h4>Sender</h4>
{% highlight cpp %}
#include <nozzle/nozzle.hpp>

nozzle::sender_desc desc;
desc.name = "my_output";
desc.application_name = "MyApp";
desc.ring_buffer_size = 3;
auto sender = nozzle::sender::create(std::move(desc)).value();

nozzle::texture_desc td;
td.width = 1920;
td.height = 1080;
td.format = nozzle::texture_format::rgba8_unorm;
auto frame = sender.acquire_writable_frame(td).value();

// ... write GPU data into frame ...

sender.commit_frame(frame);
{% endhighlight %}

</div>
<div>

<h4>Receiver</h4>
{% highlight cpp %}
#include <nozzle/nozzle.hpp>

nozzle::receiver_desc desc;
desc.name = "my_output";
desc.application_name = "MyViewer";
auto receiver = nozzle::receiver::create(std::move(desc)).value();

nozzle::acquire_desc ad;
ad.timeout_ms = 1000;
auto frame = receiver.acquire_frame(ad).value();

auto info = frame.info();
// info.width == 1920
// info.height == 1080
// info.frame_index, info.timestamp_ns ...
{% endhighlight %}

</div>
</div>

<h2>Integrations</h2>

<div class="integrations-grid">
  <a href="integrations/python.html">py.nozzle<span class="lang">Python</span></a>
  <a href="integrations/rust.html">nozzle.rs<span class="lang">Rust</span></a>
  <a href="integrations/swift.html">nozzle.swift<span class="lang">Swift</span></a>
  <a href="integrations/openframeworks.html">ofxNozzle<span class="lang">C++ / openFrameworks</span></a>
  <a href="integrations/max-msp.html">jit.nozzle<span class="lang">Max/MSP</span></a>
  <a href="integrations/touchdesigner.html">nozzle-TOP<span class="lang">TouchDesigner</span></a>
  <a href="integrations/obs.html">obs-nozzle<span class="lang">OBS Studio</span></a>
  <a href="integrations/blender.html">blender-nozzle<span class="lang">Blender</span></a>
  <a href="integrations/sokol.html">nozzle-sokol<span class="lang">sokol_gfx</span></a>
  <a href="integrations/trussc.html">tcxNozzle<span class="lang">TrussC</span></a>
</div>

<h2>Integration Status</h2>

<table>
  <thead>
    <tr><th>Integration</th><th>Module</th><th>macOS</th><th>Windows</th><th>Linux</th></tr>
  </thead>
  <tbody>
    <tr><td><a href="https://github.com/nozzle-io/py.nozzle">py.nozzle</a></td><td>—</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/nozzle.rs">nozzle.rs</a></td><td>—</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/nozzle.swift">nozzle.swift</a></td><td>—</td><td></td><td>N/A</td><td>N/A</td></tr>
    <tr><td><a href="https://github.com/nozzle-io/ofxNozzle">ofxNozzle</a></td><td>ofxNozzleSender</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/ofxNozzle">ofxNozzle</a></td><td>ofxNozzleReceiver</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/tcxNozzle">tcxNozzle</a></td><td>tcxNozzleSender</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/tcxNozzle">tcxNozzle</a></td><td>tcxNozzleReceiver</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/jit.nozzle">jit.nozzle</a></td><td>jit.nozzle.*</td><td>✅</td><td></td><td>N/A</td></tr>
    <tr><td><a href="https://github.com/nozzle-io/jit.nozzle">jit.nozzle</a></td><td>jit.gl.nozzle</td><td></td><td></td><td>N/A</td></tr>
    <tr><td><a href="https://github.com/nozzle-io/nozzle-TOP">nozzle-TOP</a></td><td>—</td><td>✅</td><td></td><td>N/A</td></tr>
    <tr><td><a href="https://github.com/nozzle-io/obs-nozzle">obs-nozzle</a></td><td>—</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/blender-nozzle">blender-nozzle</a></td><td>—</td><td></td><td></td><td></td></tr>
    <tr><td><a href="https://github.com/nozzle-io/nozzle-sokol">nozzle-sokol</a></td><td>—</td><td></td><td></td><td></td></tr>
  </tbody>
</table>

<p>nozzle draws significant inspiration from <a href="https://syphon.info/">Syphon</a> and <a href="http://spout.zeal.co/">Spout</a>. The named sender/receiver model, the concept of shared GPU textures between local processes, and the focus on creative-coding and real-time graphics integration all follow the path they established. nozzle is an independent implementation with its own API design and is not protocol-compatible with either project.</p>
