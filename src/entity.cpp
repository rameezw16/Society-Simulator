#include "../include/entity.h"

int Entity::timer = 15;
int Entity::season = 0;

void Entity::step_season() {
  if (timer != 0) {
    timer--;
    return;
  } else {
    season = (season + 1) % 4; // have to do this for some rason
    timer = 15;
  }
}

// entity
Entity::Entity(const int pos_x, const int pos_y, const int spritesheet_pos_x,
               const int spritesheet_pos_y)
    : spritesheet_pos_x(spritesheet_pos_x),
      spritesheet_pos_y(spritesheet_pos_y), pos_x(pos_x), pos_y(pos_y){};
Entity::~Entity() = default;

void Entity::set_position(const int pos_x, const int pos_y) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
};

void Entity::set_sprite(const int spritesheet_pos_x,
                        const int spritesheet_pos_y) {
  this->spritesheet_pos_x = spritesheet_pos_x;
  this->spritesheet_pos_y = spritesheet_pos_y;
}

int Entity::get_spritesheet_pos_x() const { return spritesheet_pos_x; };
int Entity::get_spritesheet_pos_y() const { return spritesheet_pos_y; };

void Entity::decay() {};
// std::string Entity::get_type() {return this->type;};

// bool Entity::get_walkable() const {return this->walkable;};

// terrain
