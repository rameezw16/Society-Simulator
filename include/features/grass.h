#pragma once
#include "./feature.h"



class Grass : public Feature {
public:
	Grass(const int pos_x, const int pos_y, const int spritesheet_pos_x = 1, const int spritesheet_pos_y = 28);
	~Grass();
};

