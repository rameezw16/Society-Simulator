#pragma once
#include "./entity.h" //spritesheet is included here already
#include "./perlin.h"
#include <SDL2/SDL.h>
#define SIZE_X 600
#define SIZE_Y 600

// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture,
       Spritesheet *spritesheet)
      : window(window), renderer(renderer), texture(texture),
        spritesheet(spritesheet) {

    randomly_generate();
  };

  void randomly_generate();

  void draw_grid();

private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Texture *texture;
  Spritesheet *spritesheet;

  Entity **entity_grid;
};
