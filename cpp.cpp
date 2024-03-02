#include <SDL2/SDL.h>

#include <complex>
#include <stdio.h>
#include <string>

#define ITER_MAX_DEF 30

constexpr int W = 400;
constexpr int H = 300;
constexpr int HW = W / 2;
constexpr int HH = H / 2;

constexpr float zoomx = 3.f / H;
constexpr float zoomy = 3.f / H;

constexpr float scalex = 1.f;
constexpr float scaley = 1.f;

int main(int argc, char** argv) {
	/* TODO: Add error handling */
	Uint32 fstart;
	uint8_t color;
	char fps[12];
	int iter_max;

	argc < 2 ? (iter_max = ITER_MAX_DEF) : (iter_max = std::stoi(argv[1]));
	printf("Max iterations: %d\n", iter_max);

	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window* window = SDL_CreateWindow("Simple Mandelbrot Fractal plotter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W * scalex, H * scaley, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_RenderSetLogicalSize(renderer, W, H);

	SDL_Event e;
	
	while (1) {
		fstart = SDL_GetTicks();
		for (int x=0; x < W; x++) {
			for (int y=0; y < H; y++) {
				std::complex<float> c((x - HW) * zoomx, (y - HH) * zoomy); 
				std::complex<float> z(0, 0);
				int iter_count = 0;

				while (iter_count < iter_max) {
					z = (z * z) + c;
					if (abs(z) > 2) break;
					iter_count++;
				}

				// TODO: Extract colors from a texture map
				color = int(255 * iter_count / iter_max);

				SDL_SetRenderDrawColor(renderer, color, color, color, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_RenderPresent(renderer);
		sprintf(fps, "C++ %.1f FPS", 1000.f / (SDL_GetTicks() - fstart));
		SDL_SetWindowTitle(window, fps);

		while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) return 0;
	}
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	
	return 0;
}
