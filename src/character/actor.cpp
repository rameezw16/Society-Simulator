#include "../../include/characters/actor.h"


Agent::Agent(const int pos_x, const int pos_y, const int spritesheet_pos_x,
				 const int spritesheet_pos_y)
	: Entity(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};

Agent::~Agent() = default;





