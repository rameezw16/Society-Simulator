#include "../include/entity.h"

Entity::Entity(const int spritesheet_pos_x, const int spritesheet_pos_y,
               const int pos_x, const int pos_y)
    : spritesheet_pos_x(spritesheet_pos_x),
      spritesheet_pos_y(spritesheet_pos_y), pos_x(pos_x), pos_y(pos_y){};

Terrain::Terrain(const int spritesheet_pos_x, const int spritesheet_pos_y,
                 const int pos_x, const int pos_y)
    : Entity(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y){};

Building::Building(const int spritesheet_pos_x, const int spritesheet_pos_y,
                   const int size_x, const int size_y, const int pos_x,
                   const int pos_y)
    : Terrain(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y),
      size_x(size_x), size_y(size_y){};

void Building::set_position(const int pos_x, const int pos_y) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
}

void Building::draw(Spritesheet *sp, SDL_Texture *texture) {
  for (int i = 0; i < this->size_x; i++) {
    for (int j = 0; i < this->size_y; j++) {
      SDL_Rect pos{pos_x + i, pos_y +j};
      sp->draw_sprite(spritesheet_pos_x + i, spritesheet_pos_y + j, &pos, texture);
    }
  }
};
