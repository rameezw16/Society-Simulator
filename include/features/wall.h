#pragma once
#include "./feature.h"

class Wall : public Feature {
public:
  Wall(const int pos_x, const int pos_y, const int spritesheet_pos_x = 8,
	   const int spritesheet_pos_y = 10);
  ~Wall();
};
