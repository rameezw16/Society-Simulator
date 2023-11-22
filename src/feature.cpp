#include "../include/feature.h"

	//add interactions
Feature::Feature(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y)
	: Terrain( pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

void Feature::draw(Spritesheet *sp, SDL_Texture *texture) {
	SDL_Rect pos{pos_x * SIZE_OCCUPIED, pos_y * SIZE_OCCUPIED, SIZE_OCCUPIED,
							 SIZE_OCCUPIED}; // blowing it up 10x
	sp->draw_sprite(spritesheet_pos_x, spritesheet_pos_y, &pos, texture);
};

//Feature::~Feature() = default;

Grass::Grass(const int pos_x, const int pos_y, const int spritesheet_pos_x,
						 const int spritesheet_pos_y)
	: Feature(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};
Grass::~Grass() = default;



/*
//building
Building::Building(
    const int spritesheet_pos_x,
    const int spritesheet_pos_y, // size_x is the size of the sprite
    const int size_x, const int size_y, const int pos_x, const int pos_y)
    : Terrain(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y),
      size_x(size_x), size_y(size_y){};
Building::~Building() = default;

void Building::draw(Spritesheet *sp, SDL_Texture *texture) {
  SDL_Rect pos{pos_x, pos_y, SIZE_OCCUPIED, SIZE_OCCUPIED};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      pos.x = (pos_x + i) * pos.w;
      pos.y = (pos_y + j) * pos.h;
      sp->draw_sprite(spritesheet_pos_x + i, spritesheet_pos_y + j, &pos,
                      texture);
    }
  }
};

Wall::Wall(const int spritesheet_pos_x, const int spritesheet_pos_y,
             const int pos_x, const int pos_y)
	: Terrain(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y) { walkable = false; }
	Wall::~Wall() = default;

*/
