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

template <typename T> class Random_Walker {
public:
  Random_Walker(unsigned int seed, std::unique_ptr<Grid<Terrain>> &terrain,
                std::unique_ptr<Grid<Feature>> &feature, int iterations = 500)
      : limit(limit), seed(seed), iterations(iterations) {
    srand(seed);
    this->terrain = std::move(terrain);
    this->feature = std::move(feature);
  };

  std::unique_ptr<Grid<Terrain>> &get_terrain() { return (this->terrain); };
  std::unique_ptr<Grid<Terrain>> &get_feature() { return (this->feature); };

  void walk_terrain(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < iterations; ++i) {
      random_walk();
      std::unique_ptr<T> current_feature = feature->get(this->x, this->y);
      std::unique_ptr<T> current_terrain = terrain->get(this->x, this->y);

      if (current_feature) {
        feature->set(this->x, this->y, nullptr);
      }

      if (current_terrain) {
        terrain->set(this->x, this->y, nullptr);
      }
      std::unique_ptr<T> new_terrain = std::make_unique<T>(this->x, this->y);

      terrain->set(this->x, this->y, new_terrain);
    }
    patch_holes();
  };

  void walk_feature(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < iterations; ++i) {
      random_walk();
      std::unique_ptr<T> current_feature = feature->get(this->x, this->y);
      std::unique_ptr<T> current_terrain = terrain->get(this->x, this->y);

      if (current_feature) {
        feature->set(this->x, this->y, nullptr);
      }

      if (current_terrain) {
        terrain->set(this->x, this->y, nullptr);
      }
      std::unique_ptr<T> new_feature = std::make_unique<T>(this->x, this->y);

      feature->set(this->x, this->y, new_feature);
    }
    patch_holes();
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
    x = proposed_x;
    y = proposed_y;

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
      }
    }
  }

  int x{SIZE / 2};
  int y{SIZE / 2}; // position

  std::unique_ptr<Grid<Terrain>> terrain;
  std::unique_ptr<Grid<Feature>> feature;

  int iterations;

  int limit = SIZE;
  unsigned int seed;
};
