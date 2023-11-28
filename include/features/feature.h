#pragma once
#include "../terrain/terrain.h"

class Feature : public Terrain { //e.g. grass, building etc.
public:
  Feature(const int pos_x, const int pos_y, const int spritesheet_pos_x,
          const int spritesheet_pos_y);
  virtual ~Feature();
  virtual void interact_randomly() override;
  bool walkable = false;

protected:
	bool natural;
};



