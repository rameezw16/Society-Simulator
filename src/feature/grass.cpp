#include "../../include/features/grass.h"

Grass::Grass(const int pos_x, const int pos_y, const int food_level,
             const int food_capacity, const int spritesheet_pos_x,
             const int spritesheet_pos_y)
    : Feature(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y),
      food_level(std::min(food_level, food_capacity)),
      food_capacity(food_capacity) {
  this->update_sprite();
  grow = false;
};
Grass::~Grass() = default;

void Grass::step() {
  this->update_sprite();
  this->consume();

  // if (grow)
  //   this->grow_back();
  // else
  //   this->consume();
}

void Grass::grow_back() {
  if (food_level < food_capacity)
    food_level++;
}

void Grass::consume() {
  if (food_level > 0)
    food_level--;
}

void Grass::update_sprite() {
  if (food_level == 0) {
    spritesheet_pos_x = 0;
    spritesheet_pos_y = 0;
    grow = ~grow;
  } else if (food_level < 10) { // barren
    spritesheet_pos_x = 26;
    spritesheet_pos_y = 13;
  } else if (food_level < 20) { // bud
    spritesheet_pos_x = 28;
    spritesheet_pos_y = 13;
  } else if (food_level < 40) { // seedling (switched w previous)
    spritesheet_pos_x = 27;
    spritesheet_pos_y = 13;
  } else if (food_level < 60) { // plant
    spritesheet_pos_x = 29;
    spritesheet_pos_y = 13;
  } else if (food_level < 80) { // tree
    spritesheet_pos_x = 30;
    spritesheet_pos_y = 13;
  } else if (food_level < 100) { // forest
    spritesheet_pos_x = 31;
    spritesheet_pos_y = 13;
    grow = ~grow;
  }
}

bool Grass::get_walkable() const { return this->walkable; };
std::string Grass::get_type() const { return this->type; };
