#pragma once
#include "builder.h"
#include "characters/agent.h"
#include "features/feature.h"
#include "grid.h"
#include "perlin.h"
#include "randomwalker.h"
#include "terrain/terrain.h"
#include "terrain/wall.h"
#include <memory>
#include <random>

using std::make_unique;
using std::unique_ptr;
// This is a builder. We create a set of grids and then give the game ownership
// of this grid. Memory is managed automatically through the use of smart
// pointers. We use Perlin generation for the heightmap and general, smooth
// features. We use random walks to add jagged edges, and to make the landscape
// more natural
//
// Unique ptrs are also used because we were facing a very difficult to track
// bug that had the 2D terrain array being overridden by some features after
// some very specific random walks. Hence we decided to control the code by
// using move semantics, to good effect

// For backwards compatibility for our old code, where Grid<T> was just an
// array. Now Grid<T> is an array of unique_ptr<T>
using pointer_terrain = unique_ptr<Terrain>;
using pointer_feature = unique_ptr<Feature>;
using pointer_agent = unique_ptr<Agent>;

class Earth_builder : public Builder {

public:
  Earth_builder(std::mt19937 &mt, unsigned int seed = 1985);
  ~Earth_builder();
  void reset();
  void general_generation() override;
  void random_walk_generation() override;
  void add_people_to_grid() override;
  void cleanup() override;

  unique_ptr<Grid<Terrain>> &get_terrain();
  unique_ptr<Grid<Feature>> &get_features();
  unique_ptr<Grid<Agent>> &get_agents();

private:
  unique_ptr<Grid<Terrain>> terrain; // this contains unique ptrs
  unique_ptr<Grid<Feature>> features;
  unique_ptr<Grid<Agent>> agents;

  Perlin perlin_food;
  Perlin perlin_earth;
  std::mt19937 mt;

  // Random_Walker<Terrain> walker_terrain;
  // Random_Walker<Feature> walker_feature;
  unsigned int seed;
};
