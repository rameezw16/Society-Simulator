#pragma once
#include "./terrain.h"

class Water
    : public Terrain { // making a class so we can extend functionality later
public:
  Water(const int pos_x, const int pos_y, const int spritesheet_pos_x = 13,
        const int spritesheet_pos_y = 19);
  ~Water();

  bool get_walkable() const override;
  std::string get_type() const override;

  void step() override;
  void consume() override;
  void grow_back() override;

  bool walkable = false; // TODO make these private
  std::string type = "water";
};
