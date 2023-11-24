#include "../../include/features/grass.h"

Grass::Grass(const int pos_x, const int pos_y, const int spritesheet_pos_x,
			 const int spritesheet_pos_y)
	: Feature(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};
Grass::~Grass() = default;
