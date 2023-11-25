#pragma once
#include "../entity.h"

class Agent : public Entity {
public:
	Agent(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y);

	virtual ~Agent();
};





