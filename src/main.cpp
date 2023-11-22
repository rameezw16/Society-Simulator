//#include "../include/entity.h"
#include "../include/terrain.h"
//#include "../include/perlin.h"
//#include "../include/grid.h"
#include "../include/spritesheet.hpp"
#include <cstring>
#include <iostream>
#define SIZE_X 600
#define SIZE_Y 600

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;
  //Perlin perlin_gen(seed);

  //SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

  Spritesheet *spritesheet =
	  new Spritesheet{"/home/hak/hw/oopProj/resources/"
					  "Bountiful-Bits-10x10-v-3.1/Colored/Full.png"};

  // Grid game_grid{win,renderer,texture,spritesheet,seed};

  Dirt a {}

  SDL_Rect rect{0, 0, SIZE_X, SIZE_Y}; // create bounding box
  while (true) {

    SDL_Event e;
    if (SDL_WaitEvent(&e)) {
      if (e.type == SDL_QUIT)
        break;
    };
	spritesheet.draw

  };

	delete spritesheet;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(win);
  SDL_Quit();
}
