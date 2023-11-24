// #include "../include/entity.h"
// #include "../include/perlin.h"
// #include "../include/grid.h"
#include "../include/spritesheet.hpp"
#include "../include/terrain/dirt.h"
#include "../include/entity.h"
#include <cstring>
#include <iostream>
#define SIZE_X 600
#define SIZE_Y 600

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;
  // Perlin perlin_gen(seed);

  // SDL_PixelFormat *pixFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);

  Drawer *drawer =
	  new Drawer{"/home/hak/hw/oopProj/resources/"
					  "Bountiful-Bits-10x10-v-3.1/Colored/Full.png"};

  // Grid game_grid{win,renderer,texture,drawer,seed};


  Entity* entity = new Dirt {10,10};


  while (true) {

	SDL_Event e;
	if (SDL_WaitEvent(&e)) {
	  if (e.type == SDL_QUIT)
		break;
	};
	drawer->draw_sprite(entity, 10, 10);
	drawer->present();
  };

  delete drawer;
}
