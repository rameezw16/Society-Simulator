#pragma once
#include "./terrain.h"

class Feature : public Terrain { //e.g. grass, building etc.
public:
  Feature(const int pos_x, const int pos_y, const int spritesheet_pos_x,
          const int spritesheet_pos_y);
  //virtual ~Feature();
  void draw(Spritesheet *sp, SDL_Texture *texture) override;
protected:
	bool natural;
};

class Grass : public Feature {
public:
	Grass(const int pos_x, const int pos_y, const int spritesheet_pos_x = 1, const int spritesheet_pos_y = 28);
	~Grass();
};


