#pragma once
#include "./terrain.h"

class Water : public Terrain { //making a class so we can extend functionality later
public:
	Water(const int pos_x, const int pos_y, const int spritesheet_pos_x = 13, const int spritesheet_pos_y = 19);
	~Water();


  bool walkable = false;
  std::string type = "water";
        
};
