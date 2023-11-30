#pragma once
#include "terrain.h"

class Dirt : public Terrain { //making a class so we can extend functionality later
public:
	Dirt(const int pos_x, const int pos_y, const int spritesheet_pos_x = 9, const int spritesheet_pos_y = 33);
  //13 and 24 for bright dirt
  //9 and 33 for darker dirt
  ~Dirt();
  std::string type = "dirt";
};



