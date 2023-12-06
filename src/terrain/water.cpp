#include "../../include/terrain/water.h"
#include <iostream>

Water::Water(const int pos_x, const int pos_y, const int spritesheet_pos_x,
			 const int spritesheet_pos_y)
	: Terrain(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

Water::~Water() = default; // need to do this to avoid vtable compilation error

bool Water::get_walkable() const {return this->walkable;};
std::string Water::get_type() const {return this->type;};

void Water::step() {
  if (season == 3)
    this->grow_back();
  else if (season == 1)
    this->consume();
//   std::cout << food_level << " " << food_capacity << " " << season << " " << timer
            // << "\n";
}

void Water::grow_back() 
{
	printf("Water trying to flood!\n");
}

void Water::consume() {
	printf("Water trying dry!\n");
}