#pragma once
#include "./features/feature.h"
#include "./perlin.h"
#include "./terrain/terrain.h"
#include "./terrain/water.h"
#include "./terrain/dirt.h"
#include "./features/grass.h"
#include "./features/wall.h"
#include "./randomwalker.h"
#include <SDL2/SDL.h>

// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(unsigned int seed = 1985);
  ~Grid();

  void randomly_generate();
  void random_walk(int x, int y);

  //making this public just for testing

  Terrain *terrain[60][60]; // grid of terrain pointers, aggregation
  Feature *feature[60][60]; // grid of features built on terrain
  Entity *character[60][60];   // grid of entities located on terrain

private:
  Perlin perlin_gen;

  Perlin temperature;
  Perlin humidity;
  Perlin evil;

  const int gridsize = 60;
};
