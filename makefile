MAX_ITER ?= 30
SDL_FLAGS = $(shell pkg-config --libs --cflags sdl2)

# GCC compiler optimizations
max = -O3
mod = -O2
OPTIMIZE ?= mod

LANG ?= c
.DEFAULT_GOAL := $(LANG)

c: c.c
	@echo "Building C example ..."
	@gcc $(OPTIMIZE) c.c -o c -lm $(SDL_FLAGS) && ./c $(MAX_ITER)

cpp: cpp.cpp
	@echo "Building C++ example ..."
	@g++ $(OPTIMIZE) cpp.cpp -o cpp $(SDL_FLAGS) && ./cpp $(MAX_ITER)

# TODO: Python build target
