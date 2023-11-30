#include "../include/Interaction_Manager.hpp"
#include "../include/characters/agent.h"
#include "../include/entity.h"
#include "../include/size.h"
#include "../include/spritesheet.hpp"
#include "../include/terrain/dirt.h"
#include <cstring>
#include <iostream>
#include <random>


const int FPS = 60;
const int frame_delay = 1000 / FPS;

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;

  char const *ss_feature =
      "../resources/Bountiful-Bits-10x10-v-3.1/Colored/Full.png";
  char const *ss_agent =
      "../resources/Bit-Bonanza-10x10-v-4.1/Colored/People.png";
  char const *ss_terrain = ss_feature;

  Drawer *drawer = new Drawer{ss_terrain, ss_feature, ss_agent};
  std::mt19937 a(static_cast<int>(seed));


  //Interaction_Manager *Int_Manager = Interaction_Manager::getInstance();

  static Uint32 next_time;

  Grid game_grid{seed};

  Uint32 frame_start;
  Uint32 frame_time;

  int count = 0;
  const int max_count = 30;

  while (true) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT)
        return 0;
    };

    frame_start = SDL_GetTicks();

    drawer->draw_grid(&game_grid);
    drawer->present();

    frame_time = SDL_GetTicks() - frame_start;
    if (count < max_count) {
      count++;
    }
    else {
      //Int_Manager->interact_all();
	  game_grid.step();
      count = 0;
    }

    if (frame_delay > frame_time)
      SDL_Delay(frame_delay - frame_time);
  };

  delete drawer;
}
