#include "../../include/terrain/wall.h"

Wall::Wall( const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y
		   )
	: Terrain(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y) {}
Wall::~Wall() = default;




