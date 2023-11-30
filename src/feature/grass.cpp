#include "../../include/features/grass.h"

Grass::Grass(const int pos_x, const int pos_y, const int food_level, const int food_capacity, const int spritesheet_pos_x,
			 const int spritesheet_pos_y)
	: Feature(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y), food_level(food_level), food_capacity(food_capacity) {};
Grass::~Grass() = default;

void Grass::step() {
  this->update_sprite();
}


void Grass::grow_back() {
  if (food_level + 1 < food_capacity) food_level++;
}


void Grass::consume() {
  if (food_level - 1 > 0) food_level--;
}

void Grass::update_sprite() {
  if (food_level == 0) { //barren
    spritesheet_pos_x = 26;
    spritesheet_pos_y = 13;
  }
  else if (food_level < 2) { //seedling
    spritesheet_pos_x = 27;
    spritesheet_pos_y = 13;
  }
  else if (food_level < 4) { //bud
    spritesheet_pos_x = 28;
    spritesheet_pos_y = 13;
  }
  else if (food_level < 6) { //plant
    spritesheet_pos_x = 29;
    spritesheet_pos_y = 13;
  }
  else if (food_level < 8) { //tree
    spritesheet_pos_x = 30;
    spritesheet_pos_y = 13;
  }
  else if (food_level < 10) { //forest
    spritesheet_pos_x = 31;
    spritesheet_pos_y = 13;
  }
}

bool Grass::get_walkable() const {return this->walkable;};
std::string Grass::get_type() const {return this->type;};
