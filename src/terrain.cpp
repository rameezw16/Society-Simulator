#include "../include/terrain.h"

Terrain::Terrain(const int pos_x, const int pos_y, const int spritesheet_pos_x,
								 const int spritesheet_pos_y)
		: Entity(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

Terrain::~Terrain() = default;

/*void Terrain::draw(Spritesheet *sp, SDL_Texture *texture) {
	SDL_Rect pos{pos_x * SIZE_OCCUPIED, pos_y * SIZE_OCCUPIED, SIZE_OCCUPIED,
							 SIZE_OCCUPIED}; // blowing it up 10x
	sp->draw_sprite(spritesheet_pos_x, spritesheet_pos_y, &pos, texture);
};
*/

Water::Water(const int pos_x, const int pos_y, const int spritesheet_pos_x,
						 const int spritesheet_pos_y)
		: Terrain(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

Water::~Water() = default; // need to do this to avoid vtable compilation error

Dirt::Dirt(const int pos_x, const int pos_y, const int spritesheet_pos_x,
					 const int spritesheet_pos_y)
		: Terrain(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};
Dirt::~Dirt() = default;
