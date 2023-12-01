#pragma once
#include "./characters/agent.h"
#include "./dir.h"
#include "./features/feature.h"
#include "./features/grass.h"
#include "./perlin.h"
#include "./randomwalker.h"
#include "./size.h"
#include "./terrain/dirt.h"
#include "./terrain/terrain.h"
#include "./terrain/wall.h"
#include "./terrain/water.h"
#include <SDL2/SDL.h>
#include <random>

// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(unsigned int seed = 1985);
  ~Grid();

  void randomly_generate();
  void destroy();
  void create_water();
  void create_fauna();
  void add_people_to_grid();

  // making this public just for testing

  bool check_move(Agent *a, Dir direction);

  void step();
  void pathfind(Agent *a);

  Terrain *terrain[SIZE][SIZE]; // grid of terrain pointers, aggregation
  Feature *feature[SIZE][SIZE]; // grid of features built on terrain
  Agent *agent[SIZE][SIZE];     // grid of entities located on terrain
  // Agent list in Agent class

private:
  Perlin perlin_gen;
  Perlin food;
  std::mt19937 mt;
  const int middle = SIZE / 2;
  const int total_iters = 500;

  const int gridsize = SIZE;
};
