#pragma once
#include "../include/entity.h"

class Terrain : public Entity {
public:
	Terrain(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y);

	virtual ~Terrain();

	//void draw(Spritesheet* sp, SDL_Texture* texture) override;
};

class Water : public Terrain { //making a class so we can extend functionality later
public:
	Water(const int pos_x, const int pos_y, const int spritesheet_pos_x = 13, const int spritesheet_pos_y = 19);
	~Water();
        
};

class Dirt : public Terrain { //making a class so we can extend functionality later
public:
	Dirt(const int pos_x, const int pos_y, const int spritesheet_pos_x = 0, const int spritesheet_pos_y = 0);
	~Dirt();
};

