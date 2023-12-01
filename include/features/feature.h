#pragma once
#include "../terrain/terrain.h"
#include <iostream>

class Feature : public Entity { // e.g. grass, building etc.
public:
  Feature(const int pos_x, const int pos_y, const int spritesheet_pos_x,
          const int spritesheet_pos_y); // by default create grass
  virtual ~Feature();

  virtual void step() = 0;
  virtual void consume() = 0;
  virtual void grow_back() = 0;

  // virtual bool get_walkable() const = 0;
  // virtual std::string get_type() const = 0;

protected:
  bool walkable = false;
  std::string type = "feature";
};
