#include "../include/entity.h"
#define SIZE_OCCUPIED 100

Entity::Entity(const int spritesheet_pos_x, const int spritesheet_pos_y,
               const int pos_x, const int pos_y)
    : spritesheet_pos_x(spritesheet_pos_x),
      spritesheet_pos_y(spritesheet_pos_y), pos_x(pos_x), pos_y(pos_y){};
Entity::~Entity() = default;

void Entity::set_position(const int pos_x, const int pos_y) {
  this->pos_x = pos_x;
  this->pos_y = pos_y;
};

Terrain::Terrain(const int spritesheet_pos_x, const int spritesheet_pos_y,
                 const int pos_x, const int pos_y)
    : Entity(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y){};

Terrain::~Terrain() = default;

void Terrain::draw(Spritesheet *sp, SDL_Texture *texture) {
  SDL_Rect pos{pos_x, pos_y, SIZE_OCCUPIED, SIZE_OCCUPIED};
  pos.x = pos_x ;
  pos.y = pos_y ;
  sp->draw_sprite(spritesheet_pos_x, spritesheet_pos_y, &pos, texture);
};

Building::Building(
    const int spritesheet_pos_x,
    const int spritesheet_pos_y, // size_x is the size of the sprite
    const int size_x, const int size_y, const int pos_x, const int pos_y)
    : Terrain(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y),
      size_x(size_x), size_y(size_y){};
Building::~Building() = default;

void Building::draw(Spritesheet *sp, SDL_Texture *texture) {
  SDL_Rect pos{pos_x, pos_y, SIZE_OCCUPIED, SIZE_OCCUPIED};
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      pos.x = pos_x + i * pos.w;
      pos.y = pos_y + j * pos.h;
      sp->draw_sprite(spritesheet_pos_x + i, spritesheet_pos_y + j, &pos,
                      texture);
    }
  }
};


Water::Water(const int spritesheet_pos_x, const int spritesheet_pos_y,
             const int pos_x, const int pos_y)
    : Terrain(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y) {
  walkable = false;
};
Water::~Water() = default; //need to do this to avoid vtable compilation error


Dirt::Dirt(const int spritesheet_pos_x, const int spritesheet_pos_y,
             const int pos_x, const int pos_y)
    : Terrain(spritesheet_pos_x, spritesheet_pos_y, pos_x, pos_y) {
  walkable = true;
};
Dirt::~Dirt() = default;

