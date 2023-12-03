#pragma once
#include "terrain.h"

class Dirt
    : public Terrain { // making a class so we can extend functionality later
public:
  Dirt(const int pos_x, const int pos_y, const int spritesheet_pos_x = 0,
       const int spritesheet_pos_y = 0);
  // 13 and 24 for bright dirt
  // 9 and 33 for darker dirt
  // 0 and 0 for darkest dirt
  ~Dirt();
  bool get_walkable() const override;
  std::string get_type() const override;
  std::string type = "dirt";
};
