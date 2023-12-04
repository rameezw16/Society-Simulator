#pragma once
#include "./feature.h"

class Grass : public Feature {
public:
  Grass(const int pos_x, const int pos_y, const int food_level = 3,
        const int food_capacity = 10, const int spritesheet_pos_x = 28,
        const int spritesheet_pos_y = 1);

  ~Grass();

  void step() override;
  bool get_walkable() const override;
  std::string get_type() const override;

private:
  bool walkable = false;
  void grow_back() override; // will grow back the level of food
  void consume() override;   // will reduce the amount of food (due to
                             // consumption)
  void update_sprite();      // will update the sprite based on food_level
  int food_level;
  int food_capacity;
  std::string type = "grass";
  bool grow = false;
};
