#pragma once
#include "../entity.h"

class Terrain : public Entity {
public:
  Terrain(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y);

  virtual ~Terrain();
  virtual bool get_walkable() const = 0;
  virtual std::string get_type() const = 0;

  bool walkable = true;

};

