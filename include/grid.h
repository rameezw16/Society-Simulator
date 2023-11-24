#pragma once
#include "./features/feature.h"
#include "./perlin.h"
#include "./terrain/terrain.h"
#include "./terrain/water.h"
#include "./terrain/dirt.h"
#include "./features/grass.h"
#include <SDL2/SDL.h>

// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, unsigned int seed = 1985);
  ~Grid();

  void randomly_generate();

private:
  Perlin perlin_gen;

  Perlin temperature;
  Perlin humidity;
  Perlin evil;

  Terrain *terrain[60][60]; // grid of terrain pointers, aggregation
  Feature *feature[60][60]; // grid of features built on terrain
  Entity *entity[60][60];   // grid of entities located on terrain
};
