#pragma once
#include "builder.h"
#include "features/feature.h"
#include "grid.h"
#include "perlin.h"
#include "randomwalker.h"
#include "terrain/terrain.h"
#include <memory>

class Earth_builder : public Builder {

public:
  Earth_builder(unsigned int seed = 1985);
  ~Earth_builder();
  void general_generation() override;
  void random_walk_generation() override;
  void cleanup() override;

  std::unique_ptr<Grid<std::unique_ptr<Terrain>>> get_terrain();
  std::unique_ptr<Grid<std::unique_ptr<Feature>>> get_features();

private:
  // Thank god you only have to see this once
  std::unique_ptr<Grid<std::unique_ptr<Terrain>>> terrain;
  std::unique_ptr<Grid<std::unique_ptr<Feature>>> features;
  Perlin perlin_food;
  Perlin perlin_terrain;
  // Random_Walker<Terrain> walker_terrain;
  // Random_Walker<Feature> walker_feature;
  unsigned int seed;
};
