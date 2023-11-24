#pragma once
#include "terrain.h"

class Dirt : public Terrain { //making a class so we can extend functionality later
public:
	Dirt(const int pos_x, const int pos_y, const int spritesheet_pos_x = 0, const int spritesheet_pos_y = 0);
	~Dirt();
	void interact_randomly() override;
};



