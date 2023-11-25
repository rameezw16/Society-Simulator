#include "../../include/characters/wolf.h"

Wolf::Wolf(const int pos_x, const int pos_y, const int spritesheet_pos_x,
				 const int spritesheet_pos_y)
	: Agent(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

Wolf::~Wolf() = default;


void Wolf::interact_randomly() {};
