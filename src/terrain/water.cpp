#include "../../include/terrain/water.h"

Water::Water(const int pos_x, const int pos_y, const int spritesheet_pos_x,
			 const int spritesheet_pos_y)
	: Terrain(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

Water::~Water() = default; // need to do this to avoid vtable compilation error
bool Water::get_walkable() const {return this->walkable;};

void Water::interact_randomly() {};
