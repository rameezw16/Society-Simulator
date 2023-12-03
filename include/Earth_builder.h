#pragma once
#include "builder.h"
#include "features/feature.h"
#include "grid.h"
#include "perlin.h"
#include "randomwalker.h"
#include "terrain/terrain.h"
#include "terrain/wall.h"
#include <memory>

using std::make_unique;
using std::unique_ptr;
using pointer_terrain = unique_ptr<Terrain>;
using pointer_feature = unique_ptr<Feature>;

class Earth_builder : public Builder {

public:
  Earth_builder(unsigned int seed = 1985);
  ~Earth_builder();
  void reset();
  void general_generation() override;
  void random_walk_generation() override;
  void cleanup() override;

  unique_ptr<Grid<Terrain>> &get_terrain();
  unique_ptr<Grid<Feature>> &get_features();

private:
  unique_ptr<Grid<Terrain>> terrain; // this contains unique ptrs
  unique_ptr<Grid<Feature>> features;
  Perlin perlin_food;
  Perlin perlin_earth;
  // Random_Walker<Terrain> walker_terrain;
  // Random_Walker<Feature> walker_feature;
  unsigned int seed;
};
