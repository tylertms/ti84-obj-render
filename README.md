## Usage
1. Install the [CE Toolchain](https://ce-programming.github.io/toolchain/static/getting-started.html]).
2. Clone this repo and build with `make`.
3. Use [TI Connect CE](https://education.ti.com/en/products/computer-software/ti-connect-ce-sw) to copy `bin/RENDER.8xp` to your calculator.
4. Install [clibs](https://github.com/CE-Programming/libraries/) to your calculator if needed.
5. Run PRGM->RENDER on your TI84.
6. Hold any button while a new frame starts rendering to exit the program (clear RAM in case of emergency).
   
To include your own `OBJ` file:
1. Export your model with vertex colors.
2. Place it in ~/assets as the only file.
3. Adjust `SCALE` in `main.c`, and re-run `make`.

## Limitations:
* Your `OBJ` file must fit in ~50kB.
* In practice, the rendering is fairly unoptimized here, as every triangle will be drawn once per frame (Benchmarked roughly 1 FPS at 180 triangles).
* Triangles are drawn in whatever order they appear in the `OBJ` file, depth is not calculated.
