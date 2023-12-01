#pragma once
#include "./characters/agent.h"
#include "./dir.h"
#include "./features/feature.h"
#include "./features/grass.h"
#include "./grid.h"
#include "./perlin.h"
#include "./randomwalker.h"
#include "./size.h"
#include "./terrain/dirt.h"
#include "./terrain/terrain.h"
#include "./terrain/wall.h"
#include "./terrain/water.h"
#include <SDL2/SDL.h>
#include <memory>
#include <random>

class Game {
public:
  Game(unsigned int seed = 1985);
  ~Game();

  void randomly_generate();
  void create_walls();
  void create_water();
  void create_fauna();
  void populate();

  // making this public just for testing
  bool check_move(Agent *a, Dir direction);
  void step();
  void pathfind(Agent *a);

private:
  Grid<std::unique_ptr<Terrain>> terrain;
  Grid<std::unique_ptr<Feature>> features;
  Grid<std::unique_ptr<Agent>> agents;

  Perlin perlin_gen;

  const int middle = SIZE / 2;
  const int total_iters = 500;
  const int gridsize = SIZE;
};
