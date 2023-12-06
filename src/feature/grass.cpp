#include "../../include/features/grass.h"


Grass::Grass(const int pos_x, const int pos_y, const int food_level,
             const int food_capacity, const int spritesheet_pos_x,
             const int spritesheet_pos_y)
    : Feature(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y),
      food_level(std::min(food_level, food_capacity)),
      food_capacity(food_capacity) {
  this->update_sprite();
  // grow = false;
  // timer = 10;
};
Grass::~Grass() = default;

void Grass::step() {
  if (season == 0)
    this->grow_back();
  else if (season == 2)
    this->decay();
  // std::cout << food_level << " " << food_capacity << " " << season << " " << timer
            // << "\n";

  this->update_sprite();
}

void Grass::grow_back() {
  food_level = std::min(food_level + 2, food_capacity);
}

void Grass::decay() { food_level = std::max(food_level - 1, 0); }
void Grass::consume() { food_level = std::max(food_level - 20, 0); }

void Grass::update_sprite() {
  if (food_level == 0) { // nothing
    spritesheet_pos_x = 0;
    spritesheet_pos_y = 0;
  } else if (food_level < 10) { // bud
    spritesheet_pos_x = 26;
    spritesheet_pos_y = 13;
  } else if (food_level < 20) { // seedling (switched w previous)
    spritesheet_pos_x = 27;
    spritesheet_pos_y = 13;
  } else if (food_level < 40) { // tree
    spritesheet_pos_x = 30;
    spritesheet_pos_y = 13;
  } else if (food_level < 60) { // forest
    spritesheet_pos_x = 31;
    spritesheet_pos_y = 13;
  }
}

bool Grass::get_walkable() const { return this->walkable; };
int Grass::get_level() const { return this->food_level; };
std::string Grass::get_type() const { return this->type; };
