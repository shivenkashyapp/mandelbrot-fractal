#include <SDL2/SDL.h>
#include <complex>
#include <iostream>

using namespace std;

constexpr int W = 400;
constexpr int H = 300;
constexpr int HW = W / 2;
constexpr int HH = H / 2;

constexpr float zoomx = 2.f / W;
constexpr float zoomy = 2.f / H;

constexpr float scalex = 3.f;
constexpr float scaley = 3.f;

constexpr int iter_max = 20;

int main() {
	/* TODO: Add error handling */
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_Window* window = SDL_CreateWindow("Simple Mandelbrot Fractal plotter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W * scalex, H * scaley, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_RenderSetLogicalSize(renderer, W, H);

	SDL_Event e;
	for ( ;; ) {
		for (int x=0; x < W; x++) {
			for (int y=0; y < H; y++) {
				complex<float> c((x - HW) * zoomx, (y - HH) * zoomy); 
				complex<float> z(0, 0);
				int iter_count = 0;

				while (iter_count < iter_max) {
					z = (z * z) + c;
					if (abs(z) > 2) break;
					iter_count++;
				}

				// TODO: Extract colors from a texture map
				uint8_t color = int(255 * iter_count / iter_max);

				SDL_SetRenderDrawColor(renderer, color, color, color, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_RenderPresent(renderer);

		while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) return 0;
		// SDL_Delay(10);
	}
	
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
