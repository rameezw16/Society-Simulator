#pragma once
#include "../entity.h"

class Terrain : public Entity {
public:
	Terrain(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y);

	virtual ~Terrain();

	//void draw(Drawer* sp, SDL_Texture* texture) override;
};

