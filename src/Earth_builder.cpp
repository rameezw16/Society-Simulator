#include "../include/Earth_builder.h"

Earth_builder::Earth_builder(unsigned int seed)
    : seed(seed), perlin_food(seed * 2), perlin_earth(seed) {
  perlin_food.add_octave(0.3, 5);
  perlin_earth.add_octave(0.6, 5);
  this->reset();
};

void Earth_builder::reset() {
  this->terrain = make_unique<Grid<Terrain>>();
  this->features = make_unique<Grid<Feature>>();
}

Earth_builder::~Earth_builder() = default;

void Earth_builder::general_generation() {
  // first fauna is generated

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      int level = static_cast<int>(perlin_food.get_noise(i, j) * 100);

      pointer_feature fauna_at_point;
      fauna_at_point = make_unique<Grass>(i, j, level, 100);
      features->set(i, j, fauna_at_point);
      // std::cout << level << " ";
    }
  }

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      int seed = static_cast<int>(perlin_earth.get_noise(i, j) * 100);

      pointer_terrain terrain_at_point;
      if (seed < 20) {
        terrain_at_point = make_unique<Water>(i, j);
      } else if (seed < 60) {
        terrain_at_point = make_unique<Dirt>(i, j);
      } else if (seed < 100) {
        terrain_at_point = make_unique<Wall>(i, j);
      } else {
        terrain_at_point = make_unique<Water>(i, j);
      }

      terrain->set(i, j, terrain_at_point);
    }
  }
}

void Earth_builder::random_walk_generation() {
  Random_Walker<Water> water_walker{seed, terrain, features, 500};
  water_walker.walk_terrain(0, 0);
  water_walker.walk_terrain(10, SIZE);
  water_walker.walk_terrain(SIZE / 2, SIZE / 2);
  water_walker.walk_terrain(10, SIZE);
  water_walker.walk_terrain(10, SIZE);
  terrain = std::move(water_walker.get_terrain());
  features = std::move(water_walker.get_features());

  Random_Walker<Wall> wall_walker{seed, terrain, features, 500};
  wall_walker.walk_terrain(0, 0);
  wall_walker.walk_terrain(SIZE, SIZE);
  wall_walker.walk_terrain(50, 50);
  wall_walker.walk_terrain(10, 10);
  wall_walker.walk_terrain(SIZE, 0);
  terrain = std::move(wall_walker.get_terrain());
  features = std::move(wall_walker.get_features());

  Random_Walker<Grass> grass_walker{seed, terrain, features, 500};
  grass_walker.walk_feature(0, 0);
  grass_walker.walk_feature(SIZE, SIZE);
  grass_walker.walk_feature(50, 50);
  grass_walker.walk_feature(10, 10);
  grass_walker.walk_feature(SIZE, 0);
  terrain = std::move(grass_walker.get_terrain());
  features = std::move(grass_walker.get_features());
}

void Earth_builder::cleanup() {}

unique_ptr<Grid<Terrain>> &Earth_builder::get_terrain() {
  return (this->terrain);
}

unique_ptr<Grid<Feature>> &Earth_builder::get_features() {
  return (this->features);
}
