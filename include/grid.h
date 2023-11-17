#pragma once
#include "./entity.h" //spritesheet is included here already
#include "./perlin.h"
#include <SDL2/SDL.h>

// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture,
       Spritesheet* spritesheet, unsigned int seed = 1985);
	~Grid();

  void randomly_generate();

  void draw_grid();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  Spritesheet *spritesheet;
	Perlin perlin_gen;

	Terrain* terrain[60][60]; //grid of terrain pointers, aggregation
  Entity **entity_grid;
};
