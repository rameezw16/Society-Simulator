#pragma once
#include "entity.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

class Drawer {
public:
  Drawer(char const *path);
  ~Drawer();

  //just make this guy take in an entity type
  void draw_sprite(Entity* entity, const int x, const int y); // draw the nth sprite, will use an
										  // enum to make this easier

  void present();

private:
  SDL_Rect clip;
  SDL_Window *window;
  SDL_Texture *spritesheet_texture_1; //these are terrain and features
  SDL_Texture *spritesheet_texture_2; //these are items and characters 
  SDL_Texture *texture;
  SDL_Renderer *renderer;

  int height;
  int width;
};
