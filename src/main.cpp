#include "../include/entity.h"
#include "../include/perlin.h"
#include <cstring>
#include <iostream>

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;
  Perlin perlin_gen(seed);

  SDL_Window *win = SDL_CreateWindow("window", 0, 0, SIZE_X, SIZE_Y,
                                     SDL_WINDOW_ALLOW_HIGHDPI);
  SDL_Renderer *renderer = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

  SDL_Texture *texture =
      SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_STATIC, SIZE_X, SIZE_Y);

  SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

  Uint32 Pixels[SIZE_X * SIZE_Y]{};
  // compartmentalize this

  perlin_gen.add_octave(0.1f, 5);
  perlin_gen.add_octave(0.3f, 5);
  perlin_gen.add_octave(0.9f, 5);

  perlin_gen.display(Pixels);

  SDL_UpdateTexture(texture, NULL, Pixels, sizeof(Uint32) * SIZE_X);
  Spritesheet bit_bonanza{"/home/hak/hw/oopProj/resources/"
                          "Bountiful-Bits-10x10-v-3.1/Colored/Full.png",
                          renderer};

	Building fortress {22,1,3,3,4,4};

  while (true) {

    SDL_Event e;
    if (SDL_WaitEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
    };

    SDL_RenderClear(renderer);
    SDL_Rect rect{0, 0, SIZE_X, SIZE_Y}; // create bounding box
    //SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);

    SDL_Rect position;

    position.w = 100;
    position.h = 100;
    //bit_bonanza.draw_sprite(22, 2, &position, texture);
    //bit_bonanza.draw_sprite(10, 10, &position, texture);

		fortress.draw(&bit_bonanza,texture);

		//SDL_RenderCopyEx(renderer, texture, NULL, &rect, 0, NULL, SDL_FLIP_NONE);

		SDL_RenderPresent(renderer);
  };

  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
