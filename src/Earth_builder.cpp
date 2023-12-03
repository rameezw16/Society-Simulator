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
      int level = static_cast<int>(perlin_food.get_noise(i, j) * 100) % 10;

      pointer_feature fauna_at_point;
      fauna_at_point = make_unique<Grass>(i, j, level);
      features->set(i, j, fauna_at_point);
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
  Random_Walker<Water> water_walker{seed, terrain, features, 10};
  water_walker.walk_terrain(10, 10);

  terrain = std::move(water_walker.get_terrain());
  features = std::move(water_walker.get_features());
}

void Earth_builder::cleanup() {}

unique_ptr<Grid<Terrain>> &Earth_builder::get_terrain() {
  return (this->terrain);
}

unique_ptr<Grid<Feature>> &Earth_builder::get_features() {
  return (this->features);
}
