## Usage
1. Install the [CE Toolchain](https://ce-programming.github.io/toolchain/static/getting-started.html]).
2. Clone this repo and build with `make`.
3. Use [TI Connect CE](https://education.ti.com/en/products/computer-software/ti-connect-ce-sw) to copy `bin/RENDER.8xp` to your calculator.

To include your own `OBJ` file, export your model with vertex colors and adjust `SCALE` in `main.c`.

## Limitations:
* Your `OBJ` file must fit in ~50kB.
* In practice, the rendering is fairly unoptimized here, as every triangle will be drawn once per frame (Benchmarked roughly 1 FPS at 180 triangles).
* Triangles are drawn in whatever order they appear in the `OBJ` file, depth is not calculated.
