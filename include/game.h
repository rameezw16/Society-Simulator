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
#include "Earth_builder.h"
#include <SDL2/SDL.h>
#include <memory>
#include <random>

class Game {
public:
  Game(unsigned int seed = 1985);
  ~Game();

  pointer_terrain &get_terrain(int i, int j);
  pointer_feature &get_feature(int i, int j);

  unique_ptr<Agent> &get_agents(int i, int j);

private:
  unique_ptr<Grid<pointer_terrain>> terrain;
  unique_ptr<Grid<pointer_feature>> features;

  unique_ptr<Grid<unique_ptr<Agent>>> agents;

  std::mt19937 mt;

  const int middle = SIZE / 2;
  const int total_iters = 500;
  const int gridsize = SIZE;
};
