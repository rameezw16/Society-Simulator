#pragma once
#include "../entity.h"

class Actor : public Entity {
public:
	Actor(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y);

	virtual ~Actor();
};





