#pragma once
#include "actor.h"

class Wolf : public Agent { //making a class so we can extend functionality later
public:
	Wolf(const int pos_x, const int pos_y, const int spritesheet_pos_x = 0, const int spritesheet_pos_y = 0);
	~Wolf();
	//void interact_randomly() override;
};








