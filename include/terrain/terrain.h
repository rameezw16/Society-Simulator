#pragma once
#include "../entity.h"

class Terrain : public Entity {
public:
  Terrain(const int pos_x, const int pos_y, const int spritesheet_pos_x,
          const int spritesheet_pos_y);

  virtual ~Terrain();
  void step() override;
  void consume() override;
  void grow_back() override;

protected:
  bool walkable = true;
  std::string type = "terrain";
};
