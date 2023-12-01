#include "../include/Earth_builder.h"

Earth_builder::Earth_builder(unsigned int seed)
    : seed(seed), perlin_food(seed * 2), perlin_earth(seed) {
  perlin_food.add_octave(0.3, 5);
  perlin_earth.add_octave(0.6, 5);
  this->reset();
};

void Earth_builder::reset() {
  this->terrain = std::make_unique<Grid<std::unique_ptr<Terrain>>>();
  this->features = std::make_unique<Grid<std::unique_ptr<Feature>>>();
}

Earth_builder::~Earth_builder() = default;

void Earth_builder::general_generation() {
  // first fauna is generated

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      int level = static_cast<int>(perlin_food.get_noise(i, j)) % 10;

      std::unique_ptr<Feature> fauna_at_point;
      fauna_at_point = std::make_unique<Grass>(Grass{i, j, level});
      features->set(i, j, fauna_at_point);
    }
  }
}

void Earth_builder::random_walk_generation() {}

void Earth_builder::cleanup() {}

std::unique_ptr<Grid<std::unique_ptr<Terrain>>> Earth_builder::get_terrain() {
  return std::move(this->terrain);
}

std::unique_ptr<Grid<std::unique_ptr<Feature>>> Earth_builder::get_features() {
  return (this->features);
}
