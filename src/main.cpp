#include "../include/spritesheet.hpp"
#include "../include/terrain/dirt.h"
#include "../include/entity.h"
#include <cstring>
#include <iostream>

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;

  Drawer *drawer = new Drawer{"/home/hak/hw/oopProj/resources/"
							  "Bountiful-Bits-10x10-v-3.1/Colored/Full.png"};

  Grid game_grid{seed};
  while (true) {

	SDL_Event e;
	if (SDL_WaitEvent(&e)) {
	  if (e.type == SDL_QUIT)
		break;
	};
	drawer->draw_grid(&game_grid);
	drawer->present();
  };

  delete drawer;
}
