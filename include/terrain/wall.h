#pragma once
#include "./terrain.h"
#include <string>

class Wall : public Terrain {
public:
  Wall(const int pos_x, const int pos_y, const int spritesheet_pos_x = 9,
       const int spritesheet_pos_y = 10);
  ~Wall();
  bool get_walkable() const override;
  std::string get_type() const override;
  bool walkable = false; // TODO make these private
  std::string type = "wall";
};
