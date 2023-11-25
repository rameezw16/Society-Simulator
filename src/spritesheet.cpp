#include "../include/spritesheet.hpp"
Drawer::Drawer(char const *ss_terrain, char const *ss_feature, char const *ss_agent) {
  this->width = SIZE * 10 ;
  this->height = SIZE * 10;

  this->window = SDL_CreateWindow("window", 0, 0, this->width, this->height, SDL_WINDOW_ALLOW_HIGHDPI);

  this->renderer = SDL_CreateRenderer(
	  window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);

  this->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
										   SDL_TEXTUREACCESS_STATIC, SIZE, SIZE);

  this->ss_terrain = IMG_LoadTexture(renderer, ss_terrain);
  this->ss_feature = IMG_LoadTexture(renderer, ss_feature);
  this->ss_agent = IMG_LoadTexture(renderer, ss_agent);


  clip.w = 10; 
  clip.h = 10;
};

Drawer::~Drawer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyTexture(texture);
  SDL_DestroyWindow(window);
};

void Drawer::draw_sprite(Terrain* entity, const int x, const int y) {
  //get coords in pixels
  clip.x = entity->get_spritesheet_pos_x() * 10;
  clip.y = entity->get_spritesheet_pos_y() * 10;

  clip.w = 10;
  clip.h = 10;

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = 10;
  position.h = 10;

  SDL_RenderCopy(renderer, ss_terrain, &clip, &position);
};


void Drawer::draw_sprite(Feature* entity, const int x, const int y) {
  // get coords in pixels
  clip.x = entity->get_spritesheet_pos_x() * 10;
  clip.y = entity->get_spritesheet_pos_y() * 10;

  clip.w = 10;
  clip.h = 10;

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = 10;
  position.h = 10;

  SDL_RenderCopy(renderer, ss_feature, &clip, &position);
};


void Drawer::draw_sprite(Agent* entity, const int x, const int y) {
  // get coords in pixels
  clip.x = entity->get_spritesheet_pos_x() * 10;
  clip.y = entity->get_spritesheet_pos_y() * 10;

  clip.w = 10;
  clip.h = 10;

  SDL_Rect position;
  position.x = x;
  position.y = y;
  position.w = 10;
  position.h = 10;

  SDL_RenderCopy(renderer, ss_agent, &clip, &position);
};






void Drawer::draw_grid(Grid *grid) {
  for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	  Terrain* terrain = grid->terrain[i][j];
	  Feature* feature = grid->feature[i][j]; 
	  Agent* agent = grid->agent[i][j]; 
	  int draw_pos_x = i * 10;
	  int draw_pos_y = j * 10;
	  //Character* character = grid->character[i][j]; 
	  if (terrain) draw_sprite(terrain, draw_pos_x, draw_pos_y);
	  if (feature) draw_sprite(feature, draw_pos_x, draw_pos_y);
	  if (agent) draw_sprite(agent, draw_pos_x, draw_pos_y);
	}
  }
}

void Drawer::present() {SDL_RenderPresent(renderer);};
