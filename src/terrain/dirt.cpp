#include "../../include/terrain/dirt.h"

Dirt::Dirt(const int pos_x, const int pos_y, const int spritesheet_pos_x,
		   const int spritesheet_pos_y)
	: Terrain(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};
Dirt::~Dirt() = default;

bool Dirt::get_walkable() const {return this->walkable;};

void Dirt::interact_randomly() {};
