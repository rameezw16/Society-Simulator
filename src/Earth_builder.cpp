#include "../include/Earth_builder.h"

Earth_builder::Earth_builder(unsigned int seed)
    : seed(seed), perlin_food(seed * 2), perlin_terrain(seed){};
Earth_builder::~Earth_builder() = default;

void Earth_builder::general_generation() {
  // first fauna is generated
  perlin_food.add_octave(0.3, 5);
}

void Earth_builder::random_walk_generation() {}

void Earth_builder::cleanup() {}

std::unique_ptr<Grid<std::unique_ptr<Terrain>>> get_terrain();
