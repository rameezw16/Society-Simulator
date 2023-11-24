#pragma once
#include <SDL2/SDL.h>
// #include "./spritesheet.hpp"
#define SIZE_OCCUPIED 10

class Entity {
public:
  Entity(const int pos_x, const int pos_y, const int spritesheet_pos_x,
		 const int spritesheet_pos_y);

  virtual ~Entity();
  virtual void interact_randomly() = 0;

  void set_position(const int pos_x,
					const int pos_y); // set top left corner of the sprite
  // virtual void draw(Spritesheet* sp, SDL_Texture* texture) = 0;

  void set_sprite(const int spritesheet_pos_x,
				  const int spritesheet_pos_y);

  int get_spritesheet_pos_x() const;
  int get_spritesheet_pos_y() const;


protected:
  int pos_x;
  int pos_y;
  int spritesheet_pos_x;
  int spritesheet_pos_y;
};
