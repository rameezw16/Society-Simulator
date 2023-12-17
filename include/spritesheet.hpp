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

// This is where we draw sprites. The drawer class takes as input paths to the
// spritesheets. Each agent has its own spritesheet. Each entity carries with it
// spritesheet coordinates, which this class will display. This is a facade for
// our SDL class.

class Drawer {
public:
  Drawer(char const *ss_terrain, char const *ss_feature, char const *ss_agent);
  ~Drawer();

  void draw_game(Game &game);
  void present();
  void flush();
  void draw_agents();

  void play_audio();
  void draw_sprite(const std::unique_ptr<Terrain> &entity, const int x,
                   const int y);
  void draw_sprite(const std::unique_ptr<Feature> &entity, const int x,
                   const int y);
  void draw_sprite(const std::unique_ptr<Agent> &entity, const int x,
                   const int y);

private:
  SDL_Rect clip;
  SDL_Window *window;
  SDL_Texture *ss_terrain;
  SDL_Texture *ss_feature;
  SDL_Texture *ss_agent;
  SDL_Texture *texture;
  SDL_Renderer *renderer;

  SDL_AudioSpec wavSpec;
  SDL_AudioDeviceID deviceID;
  Uint32 wavLength;
  Uint8 *wavBuffer;

  int height;
  int width;
};
