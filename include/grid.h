#pragma once
#include "./features/feature.h"
#include "./perlin.h"
#include "./terrain/terrain.h"
#include "./terrain/water.h"
#include "./terrain/dirt.h"
#include "./features/grass.h"
#include "./features/wall.h"
#include "./randomwalker.h"
#include "./characters/actor.h"
#include "./size.h"
#include "Interaction_Manager.hpp"
#include <random>
#include <SDL2/SDL.h>


// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(unsigned int seed = 1985);
  ~Grid();

  void perlin_generation();
  void random_walk_generation();
  void seed_people();
  //void random_walk(int x, int y);

  void step();

  //making this public just for testing

  Terrain *terrain[SIZE][SIZE]; // grid of terrain pointers, aggregation
  Feature *feature[SIZE][SIZE]; // grid of features built on terrain
  //Agent *agent[SIZE][SIZE];   // grid of entities located on terrain
  //Agent list in Agent class

private:
  Perlin perlin_gen;
  std::mt19937 mt; 
  Interaction_Manager* interaction_manager;

  Perlin temperature;
  Perlin humidity;
  Perlin evil;

  const int gridsize = SIZE;
};
