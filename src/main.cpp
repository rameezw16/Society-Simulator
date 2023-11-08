#include "../include/perlin.h"
#include <iostream>
#include <cstring>

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

	SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

	int xOrg = 100000;
	int yOrg = xOrg;

	float freq = 0.9f;
	int depth = 5;
	int scale = 10;

	Uint32 Pixels[win_width * win_height];

	for (int y = 0; y < win_height; y++) {
		for (int x = 0; x < win_width; x++) {
			float xCoord = xOrg + x / ((float)win_width) * scale; // coarseness
			float yCoord = yOrg + y / ((float)win_height) * scale;
			float perlin = perlin_gen.perlin_2d(yCoord, xCoord, freq, depth);
			Uint8 color = 255 * perlin;
			Pixels[y * win_width + x] =
					SDL_MapRGBA(pixFormat, color, color, color, 255); // grayscale
		};
	};

	SDL_UpdateTexture(texture, NULL, Pixels, sizeof(Uint32) * win_width);

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
