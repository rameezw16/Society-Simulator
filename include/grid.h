#pragma once
#include "./feature.h"
#include "./perlin.h"
#include "./terrain.h"
#include <SDL2/SDL.h>

// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture,
       Spritesheet *spritesheet, unsigned int seed = 1985);
  ~Grid();

  void randomly_generate();

  void draw_grid();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  Spritesheet *spritesheet;

  Perlin perlin_gen;

  Perlin temperature;
  Perlin humidity;
  Perlin evil;

  Terrain *terrain[60][60]; // grid of terrain pointers, aggregation
  Feature *feature[60][60]; // grid of features built on terrain
  Entity *entity[60][60];   // grid of entities located on terrain
};
