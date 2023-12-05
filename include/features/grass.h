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
  int get_level() const override; // get vegetation level
  std::string get_type() const override;
  static void step_season();
  

private:
  bool walkable = true;
  void grow_back() override; // will grow back the level of food
  void decay() override;     // natural decay due to season
  void consume() override;   // will reduce the amount of food (due to
                             // consumption)
  void update_sprite();      // will update the sprite based on food_level
  int food_level;
  int food_capacity;
  std::string type = "grass";
  static int season;
  static int timer;
};
