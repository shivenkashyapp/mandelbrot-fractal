#include <SDL2/SDL.h>

#include <stdio.h>
#include <complex.h>

/* Processing dimensions */
#define W 400
#define H 300
#define CX (float)(W)/2
#define CY (float)(H)/2
/* scaling factors to upscale/downscale processing dimensions. */
#define SX 2.f
#define SY 2.f
/* Scaled dimensions */
#define SW W*SX
#define SH H*SY

/* Offset a point relative to the center */
#define offsetx(x) ((float)x - CX)
#define offsety(y) ((float)y - CY)

#define zoom_out_factor 2.2
#define zoom_out(x) (x * zoom_out_factor / H)

// More iterations implies better visual representation, 
// but a lot more CPU usage, and a much higher render times.
#define _max_iter 30

int main(int argc, char **argv) {
	Uint32 fstart;
	char fps[10];
	uint8_t iter_count;
	uint16_t max_iter;
	
	argc < 2 ? (max_iter = _max_iter) : (max_iter = atoi(argv[1]));
	printf("Max iterations: %d\n", max_iter);

	Uint32 color;
	float max_fps = 0.0f;

	SDL_Init(SDL_INIT_VIDEO);	
	SDL_Window* window = SDL_CreateWindow("simple.c", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SW, SH, SDL_WINDOW_SHOWN);	
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_RenderSetLogicalSize(renderer, W, H);
	SDL_Event e;
	for (;;) {
		fstart = SDL_GetTicks();
		for (int x=0; x < W; x++) {
			for (int y=0; y < H; y++) {
				double complex c = zoom_out(offsetx(x)) + zoom_out(offsety(y)) * I;
				double complex z = 0 + 0 * I;
				
				iter_count = 0;
				while (iter_count < max_iter) {
					z = (z*z) + c;
					if (cabs(z) > 2) break;
					iter_count++;	
				}	
				/* TODO: Extract colors from a texture map */
				color = 255 * ((float)iter_count / max_iter);
				SDL_SetRenderDrawColor(renderer, color, color, color, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}

		SDL_RenderPresent(renderer);

		/* TODO: Better way to handle sprintf overflows? Handle destination sizes dynamically. */
		sprintf(fps, "C %.1f FPS", 1000.f / (SDL_GetTicks() - fstart));
		SDL_SetWindowTitle(window, fps);


		while (SDL_PollEvent(&e)) if (e.type == SDL_QUIT) return 0;
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}
