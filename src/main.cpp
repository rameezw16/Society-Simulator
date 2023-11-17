//#include "../include/entity.h"
//#include "../include/perlin.h"
#include "../include/grid.h"
#include <cstring>
#include <iostream>
#define SIZE_X 600
#define SIZE_Y 600

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



  Spritesheet* spritesheet = new Spritesheet{"/home/hak/hw/oopProj/resources/"
                          "Bountiful-Bits-10x10-v-3.1/Colored/Full.png",
                          renderer};
	

	Grid game_grid{win,renderer,texture,spritesheet,13};

	SDL_Rect rect{0, 0, SIZE_X, SIZE_Y}; // create bounding box
	while (true) {

    SDL_Event e;
    if (SDL_WaitEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
    };

    SDL_RenderClear(renderer);

		game_grid.draw_grid();

		SDL_RenderPresent(renderer);
  };

	delete spritesheet;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
