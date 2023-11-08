#include "../include/perlin.h"

int main(int argc, char** argv) { //takes in seed as cli argument
	unsigned int seed = (argc-1) ? std::stoi(argv[1]) : 1985;
	Perlin perlin_gen(seed);
	const int win_height = 600;
	const int win_width = 600;
	SDL_Window *win = SDL_CreateWindow("window", 0, 0, win_width, win_height,
																		 SDL_WINDOW_ALLOW_HIGHDPI);
	SDL_Renderer *renderer = SDL_CreateRenderer(
			win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

	SDL_Texture *texture =
			SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
												SDL_TEXTUREACCESS_STATIC, win_width, win_height);


	const float freq = 0.9f;
	const int depth = 5;

	Uint32 Pixels[600 * 600] {};



	SDL_UpdateTexture(texture, NULL, Pixels, sizeof(Uint32) * win_width);

	perlin_gen.set_renderer(renderer);
	perlin_gen.set_window(win);
	perlin_gen.set_texture(texture);
	perlin_gen.set_grid(Pixels);

	perlin_gen.add_octave(Pixels, 0.9f, depth);

	while (true) {
		SDL_Event e;
		if (SDL_WaitEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		};

		SDL_RenderClear(renderer);
		SDL_Rect rect{0, 0, win_width, win_height}; // create bounding box


		SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);
		SDL_RenderPresent(renderer);
	};

	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	SDL_Quit();
}
