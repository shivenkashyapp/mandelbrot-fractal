# Mandelbrot Fractal visualization
Simple Mandelbrot fractal visualization using C, C++ and SDL2.

# Running 
Clone the repo:
```sh
$ git clone https://github.com/shivenkashyapp/mandelbrot-fractal/ && cd mandelbrot-fractal
```

Build the default C example:
```sh
$ make
```

Specify a particular language (c/cpp):
```sh
$ make c
$ make c
```

(Optional) Specify GCC optimization flag:
```sh
$ make LANG=c OPTIMIZATION=-O2
```

# Weird performance results
For some reason that I haven't figured out yet, the C code on no optimization flag runs faster than the C++ code - both with the same iteration levels and the same implementation, essentially.

C with no optimizations:
![C-no-optimization](./screenshots/C.png?raw=true "C with no optimizations")

C++ with no optimizations:
![Cpp-no-optimization](./screenshots/cpp-no-opt.png?raw=true "C++ with no optimizations")

# Screenshots
![C++ output](./screenshots/cpp.png?raw=true "`C++`")
