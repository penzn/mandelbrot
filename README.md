Mandelbrot visualization in WebAssembly
=======================================

Fractal demo in WebAssembly.


## Building

Needs Clang version greater than 7, development branch would do. To build:

```
$ make
```

## Running

Requires a minimal web server to run, fetching WASM binaries over `file://` is usually disabled. For example, Python has a built in web server; in Python 3 it is started like this:

```
$ python -m http.server 8080
```

To view, navigate to http://localhost:8080
