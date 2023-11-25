#include "../include/features/feature.h"

	//add interactions
Feature::Feature(const int pos_x, const int pos_y, const int spritesheet_pos_x, const int spritesheet_pos_y)
	: Terrain( pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};


Feature::~Feature() = default;
void Feature::interact_randomly() {};

/*
Grass::Grass(const int pos_x, const int pos_y, const int spritesheet_pos_x,
						 const int spritesheet_pos_y)
	: Feature(pos_x, pos_y, spritesheet_pos_x, spritesheet_pos_y){};
Grass::~Grass() = default;
*/



