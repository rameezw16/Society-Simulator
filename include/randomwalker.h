#pragma once
#include "./features/feature.h"
#include "./features/grass.h"
#include "./size.h"
#include "./terrain/dirt.h"
#include "./terrain/wall.h"
#include "./terrain/water.h"
#include "grid.h"
#include <iostream>
#include <random>
#include <set>
#include <typeinfo>

// This is a template which takes in the "type" of walk it should conduct. For
// instance, if I am doing a dirt walk, then I will walk randomly, and wherever
// I step I will replace the area with dirt. We do have to exercise discipline,
// and use a terrain walk when we want a walk on terrain and a feature walk when
// we want a walk on features. Knowing what we know now, we probably would have
// done some kind of template inheritence, and have two different templates, one
// for features and one for terrain.

template <typename T> class Random_Walker {
public:
  Random_Walker(unsigned int seed, std::unique_ptr<Grid<Terrain>> &terrain,
                std::unique_ptr<Grid<Feature>> &feature, int iterations = 500)
      : limit(limit), seed(seed), iterations(iterations) {
    srand(seed);
    this->terrain = std::move(terrain);
    this->features = std::move(feature);
  };

  std::unique_ptr<Grid<Terrain>> &get_terrain() { return (this->terrain); };
  std::unique_ptr<Grid<Feature>> &get_features() { return (this->features); };

  void walk_terrain(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < iterations; ++i) {
      random_walk();

      std::unique_ptr<Terrain> new_terrain =
          std::make_unique<T>(this->x, this->y);

      terrain->set(this->x, this->y, new_terrain);
    }
  };

  void walk_feature(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < iterations; ++i) {
      random_walk();

      std::unique_ptr<Feature> new_feature =
          std::make_unique<T>(this->x, this->y);
      // std::unique_ptr<Terrain> new_dirt =
      //     std::make_unique<Dirt>(this->x, this->y);

      features->set(this->x, this->y, new_feature);
      // terrain->set(this->x, this->y, new_dirt);
    }
  };

private:
  void random_walk() {
    int x_dir = rand() % 3 - 1; // 0,1,2 gives -1,0,1
    int y_dir = rand() % 3 - 1;

    // if (0 > x || x >= limit)
    //   x -= 1;
    // if (0 > y || y >= limit)
    //   y -= 1;

    int proposed_x = this->x + x_dir;
    int proposed_y = this->y + y_dir;
    x = abs(proposed_x);
    y = abs(proposed_y);

    // if (0 <= proposed_x && proposed_x < limit)
    //   x = proposed_x;
    // if (0 <= proposed_y && proposed_y < limit)
    //   y = proposed_y;
  };

  void patch_holes() {
    for (int i = 0; i < limit; ++i) {
      for (int j = 0; j < limit; ++j) {
        if (terrain->get(i, j) == nullptr) {
          std::unique_ptr<Terrain> new_dirt = std::make_unique<Dirt>(i, j);
          terrain->set(i, j, new_dirt);
        }
        if (features->get(i, j) == nullptr) {
          std::unique_ptr<Feature> new_grass =
              std::make_unique<Grass>(i, j, 100, 100);
          features->set(i, j, new_grass);
        }
      }
    }
  }

  int x{SIZE / 2};
  int y{SIZE / 2}; // position

  std::unique_ptr<Grid<Terrain>> terrain;
  std::unique_ptr<Grid<Feature>> features;

  int iterations;

  int limit = SIZE;
  unsigned int seed;
};
