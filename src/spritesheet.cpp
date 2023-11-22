#include "../include/spritesheet.hpp"
Spritesheet::Spritesheet(char const *path) {
  this->width = 600;
  this->height = 600;

  this->window = SDL_CreateWindow("window", 0, 0, this->width, this->height, SDL_WINDOW_ALLOW_HIGHDPI);

  this->renderer = SDL_CreateRenderer(
	  window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

  this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
										   SDL_TEXTUREACCESS_STATIC, 600, 600);

  this->spritesheet_texture_1 = IMG_LoadTexture(renderer, path);


  // size of one sprite in pixels
  clip.w = 10; // spritesheet_image->w / col;
  clip.h = 10; // spritesheet_image->h / row;
};

Spritesheet::~Spritesheet() { SDL_DestroyTexture(texture); };

void Spritesheet::draw_sprite(Entity entity, const int x, const int y) {
  // get coords in pixels

  clip.x = entity.get_spritesheet_pos_x() * 10;
  clip.y = entity.get_spritesheet_pos_y() * 10;

  clip.w = 10;
  clip.h = 10;

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = 10;
  position.h = 10;

  SDL_RenderCopy(renderer, texture, &clip, &position);
};

void Spritesheet::present() {SDL_RenderPresent(renderer);};
