#include "../include/Interaction_Manager.hpp"
#include "../include/characters/agent.h"
#include "../include/entity.h"
#include "../include/size.h"
#include "../include/spritesheet.hpp"
#include "../include/terrain/dirt.h"
#include <boost/foreach.hpp>
#include <boost/tuple/tuple.hpp>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <random>

#define GNUPLOT_DEPRECATE_WARN
#include "../gnuplot-iostream/gnuplot-iostream.h"

const int FPS = 60;
const int frame_delay = 1000 / FPS;

int main(int argc, char **argv) { // takes in seed as cli argument
  unsigned int seed = (argc - 1) ? std::stoi(argv[1]) : 1985;
  bool plot = (argc - 2) ? std::stoi(argv[2]) : 0;

  char const *ss_feature = "../resources/Bountiful-Bits-10x10-v-3.1/Colored/"
                           "no-background/Full-no-bg.png";
  char const *ss_agent = "../resources/Bit-Bonanza-10x10-v-4.1/Colored/"
                         "People.png";
  char const *ss_terrain = ss_feature;

  Drawer *drawer = new Drawer{ss_terrain, ss_feature, ss_agent};
  std::mt19937 a(static_cast<int>(seed));

  static Uint32 next_time;

  Game game{seed};

  //  Graph Manager
  Gnuplot GNUpipe;
  bool success = false;
  if (plot) {
    FILE *data_txt = NULL;
    data_txt = fopen("../logs/data.txt", "w");
    fprintf(data_txt, "0 0\n");
    fclose(data_txt);
    FILE *GNUpipe_file = popen("${GNUPLOT_EXECUTABLE}", "w");

    if (GNUpipe_file == nullptr) {
      printf("??\n");
      std::cerr
          << "Error opening Gnuplot pipe. Make sure you have gnuplot installed "
             "and have added it as a submodule as in the readme.md"
          << std::endl;
    }
    success = true;

    GNUpipe << "set term qt persist\n";
    GNUpipe << "set title \"Population vs Season\" \n";
    GNUpipe << "set xlabel \"Season Number\" \n";
    GNUpipe << "set ylabel \"Population Size\" \n";
  }

  Uint32 frame_start;
  Uint32 frame_time;

  int count = 0;
  const int max_count = 3;

  while (true) {
    if (plot && success) {
      GNUpipe << "plot '../logs/data.txt' using 1:2 with lines lw 8 title "
                 "'Population vs Season'\n";
    }

    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT)
        return 0;
    };

    frame_start = SDL_GetTicks();

    drawer->flush();
    drawer->draw_game(game);
    drawer->present();

    frame_time = SDL_GetTicks() - frame_start;
    if (count < max_count) {
      count++;
    } else {
      game.step();
      count = 0;
    }

    if (frame_delay > frame_time)
      SDL_Delay(frame_delay - frame_time);
  };

  delete drawer;
}
