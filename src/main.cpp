#include "../include/spritesheet.hpp"
#include "../include/terrain/dirt.h"
#include "../include/entity.h"
#include "../include/size.h"
#include "../include/characters/actor.h"
#include "../include/Interaction_Manager.hpp"
#include <cstring>
#include <iostream>
#include <random>

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;

  char const* ss_feature = "/home/hak/hw/oopProj/resources/Bountiful-Bits-10x10-v-3.1/Colored/Full.png";
  char const* ss_agent = "/home/hak/hw/oopProj/resources/Bit-Bonanza-10x10-v-4.1/Colored/People.png";
  char const* ss_terrain = "/home/hak/hw/oopProj/resources/Bountiful-Bits-10x10-v-3.1/Colored/Full.png";

  Drawer *drawer = new Drawer{ss_terrain, ss_feature, ss_agent};
  std::mt19937 a (static_cast<int>(seed));


  for (int i = 0; i < 30; i++) {
	new Agent{a};
  }

  Interaction_Manager *Int_Manager = Interaction_Manager::getInstance();

  


  Grid game_grid{seed};
  while (true) {

	SDL_Event e;
	if (SDL_WaitEvent(&e)) {
	  if (e.type == SDL_QUIT)
		break;
	};
	drawer->draw_grid(&game_grid);
	drawer->present();
	Int_Manager->interact_all();
  };

  delete drawer;
}
