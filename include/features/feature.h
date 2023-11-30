#pragma once
#include "../terrain/terrain.h"

class Feature : public Terrain { //e.g. grass, building etc.
public:
  Feature(const int pos_x, const int pos_y, const int spritesheet_pos_x,
          const int spritesheet_pos_y); //by default create grass
  virtual ~Feature();
  virtual void step();



protected:
  bool walkable = false;
  std::string type = "grass";
};



