#include "../../include/features/grass.h"

Grass::Grass(const int pos_x, const int pos_y, const int food_level, const int food_capacity, const int spritesheet_pos_x,
			 const int spritesheet_pos_y)
	: Feature(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y), food_level(food_level), food_capacity(food_capacity) {};
Grass::~Grass() = default;


void Grass::grow_back() {
  if (food_level + 1 < food_capacity) food_level++;
}


void Grass::consume() {
  if (food_level - 1 > 0) food_level--;
}

void Grass::update_sprite() {
  if (food_level == 0) { //barren
    spritesheet_pos_x = 23;
    spritesheet_pos_y = 12;
  }

  else if (food_level < 3) { //seedling
    spritesheet_pos_x = 23;
    spritesheet_pos_y = 13;//13 or 12
  }
  else if (food_level < 5) { //bud
    spritesheet_pos_x = 24;
    spritesheet_pos_y = 13;
  }
  else if (food_level < 10) { //forest
    spritesheet_pos_x = 25;
    spritesheet_pos_y = 13;
  }
}
