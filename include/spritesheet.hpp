#pragma once
#include "./size.h"
#include "characters/agent.h"
#include "entity.h"
#include "features/feature.h"
#include "game.h"
#include "grid.h"
#include "terrain/terrain.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Drawer {
public:
  Drawer(char const *ss_terrain, char const *ss_feature, char const *ss_agent);
  ~Drawer();

  void draw_game(const Game &game);
  void draw_agents();
  void present();
  void flush();

private:
  std::unique_ptr<Terrain> draw_sprite(const std::unique_ptr<Terrain> entity,
                                       const int x, const int y);
  std::unique_ptr<Feature> draw_sprite(const std::unique_ptr<Feature> entity,
                                       const int x, const int y);
  std::unique_ptr<Agent> draw_sprite(const std::unique_ptr<Agent> entity,
                                     const int x, const int y);

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
