#include "../include/Earth_builder.h"

Earth_builder::Earth_builder(unsigned int seed)
    : seed(seed), perlin_food(seed * 2), perlin_earth(seed) {
  perlin_food.add_octave(0.3, 5);
  perlin_earth.add_octave(0.6, 5);
  this->reset();
};

void Earth_builder::reset() {
  this->terrain = make_unique<Grid<pointer_terrain>>();
  this->features = make_unique<Grid<pointer_feature>>();
}

Earth_builder::~Earth_builder() = default;

void Earth_builder::general_generation() {
  // first fauna is generated

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      int level = static_cast<int>(perlin_food.get_noise(i, j)) % 10;

      pointer_feature fauna_at_point;
      fauna_at_point = make_unique<Grass>(Grass{i, j, level});
      features->set(i, j, fauna_at_point);
    }
  }
}

void Earth_builder::random_walk_generation() {}

void Earth_builder::cleanup() {}

unique_ptr<Grid<pointer_terrain>> &Earth_builder::get_terrain() {
  return (this->terrain);
}

unique_ptr<Grid<pointer_feature>> &Earth_builder::get_features() {
  return (this->features);
}
