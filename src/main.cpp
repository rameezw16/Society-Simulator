#include "../include/perlin.h"
#include <cstring>
#include <iostream>

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;
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

  float freq = 0.9f;
  int depth = 5;

  Uint32 Pixels[win_width * win_height] {};

  // compartmentalize this

  perlin_gen.add_octave(Pixels, win_width, win_height, 0.9f, 5);
	/*
  for (int y = 0; y < win_height; y++) {
    for (int x = 0; x < win_width; x++) {
      Uint8 temp = 255 * Pixels[y*win_width + x];//pickColor(Pixels[y * win_width + x]);
      Pixels[y * win_width + x] =
				SDL_MapRGBA(pixFormat, temp, temp, temp, 255);
    };
  };
	*/

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
