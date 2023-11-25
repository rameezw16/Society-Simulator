#pragma once
#include "entity.h"
#include "terrain/terrain.h"
#include "features/feature.h"
#include "characters/actor.h"
#include "grid.h"
#include "./size.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Drawer {
public:
  Drawer(char const *ss_terrain, char const *ss_feature, char const *ss_agent);
  ~Drawer();

  void draw_grid(Grid* grid);
  void present();

private:
  void draw_sprite(Terrain* entity, const int x, const int y); 
  void draw_sprite(Feature* entity, const int x, const int y);
  void draw_sprite(Agent* entity, const int x, const int y);

  SDL_Rect clip;
  SDL_Window *window;
  SDL_Texture *ss_terrain; 
  SDL_Texture *ss_feature; 
  SDL_Texture *ss_agent; 
  SDL_Texture *texture;
  SDL_Renderer *renderer;

  int height;
  int width;
};
