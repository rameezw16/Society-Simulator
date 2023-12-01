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

  std::unique_ptr<Terrain> get_terrain(int i, int j);
  std::unique_ptr<Feature> get_feature(int i, int j);
  std::unique_ptr<Agent> get_agents(int i, int j);

private:
  Grid<std::unique_ptr<Terrain>> terrain;
  Grid<std::unique_ptr<Feature>> features;
  Grid<std::unique_ptr<Agent>> agents;

  std::mt19937 mt;

  const int middle = SIZE / 2;
  const int total_iters = 500;
  const int gridsize = SIZE;
};
