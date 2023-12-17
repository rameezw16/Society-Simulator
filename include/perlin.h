#pragma once
#include "./size.h"
#include <SDL2/SDL.h>
#include <algorithm>
#include <math.h>
#include <numeric>
#include <random>
#include <vector>

// This is adapted from https://en.wikipedia.org/wiki/Perlin_noise
// This is used to create a heightmap, from which we can create food and
// terrain. See Earth_Builder.h
class Perlin {
public:
  // constructors
  Perlin(unsigned int seed = 1985); // seed perlin noise

  // get noise value
  void add_octave(const double freq, const double depth);
  double get_noise(const int x, const int y);

  void display(Uint32 *Pixels);

private:
  std::vector<int> permutation;
  int block_noise(const int x, const int y) const;
  double lerp(const double x, const double y, const double m) const;
  double smooth_lerp(const double x, const double y, double m) const;
  double noise_2d(const double x, const double y) const;
  double perlin_2d(const double x, const double y, const double freq,
                   const double depth) const;

  std::mt19937 mt{}; // mersenne twister
  int seed;

  float total_noise[SIZE][SIZE]{};
  int num_octaves{};
};
