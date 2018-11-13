CC=clang
CFLAGS=-O3 --target=wasm32 -fvisibility=hidden
LFLAGS=-Wl,--import-memory,--no-entry,--strip-all,--export-dynamic,--allow-undefined-file=mandelbrot.syms -nostdlib

FILE=animation

$(FILE).wasm: $(FILE).c mandelbrot.h Makefile
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	rm -f $(FILE).wasm
