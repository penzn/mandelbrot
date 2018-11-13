Mandelbrot visualization in WebAssembly
=======================================

Fractal demo of WebAssembly.


## Building

Needs Clang version greater than 7, development build would do. Command to build:

```
$ make
```

## Running

Requires a minimal web server to run, fetching WASM binaries over `file://` is usually disabled. Python has a builtin webserver that can be started like this:

```
$ python -m http.server 8080
```

To view, havigate to http://localhost:8080