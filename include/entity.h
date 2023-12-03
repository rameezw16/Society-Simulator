#pragma once
#include <SDL2/SDL.h>
#include <string>
// #include "./spritesheet.hpp"
#define SIZE_OCCUPIED 10

class Entity {
public:
  Entity(const int pos_x, const int pos_y, const int spritesheet_pos_x,
         const int spritesheet_pos_y);

  virtual ~Entity();

  virtual bool get_walkable() const = 0;
  virtual std::string get_type() const = 0;

  void set_position(const int pos_x,
                    const int pos_y); // set top left corner of the sprite

  void set_sprite(const int spritesheet_pos_x, const int spritesheet_pos_y);

  virtual int get_spritesheet_pos_x() const;
  virtual int get_spritesheet_pos_y() const;
  virtual void step() = 0;
  virtual void consume() = 0;
  virtual void grow_back() = 0;

protected:
  bool walkable = true;
  std::string type = "entity";
  int pos_x;
  int pos_y;
  int spritesheet_pos_x;
  int spritesheet_pos_y;
};
