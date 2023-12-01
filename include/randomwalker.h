#pragma once
#include "./features/feature.h"
#include "./features/grass.h"
#include "./size.h"
#include "./terrain/dirt.h"
#include "./terrain/wall.h"
#include "./terrain/water.h"
#include <iostream>
#include <random>
#include <set>
#include <typeinfo>

#define THIS_FEATURE feature[this->x][this->y]
#define THIS_TERRAIN terrain[this->x][this->y]

template <typename T> class Random_Walker {
public:
  Random_Walker(unsigned int seed, Terrain *(&terrain)[SIZE][SIZE],
                Feature *(&feature)[SIZE][SIZE], int iterations = 500)
      : limit(limit), seed(seed), terrain(terrain), feature(feature),
        iterations(iterations) {
    srand(seed);
  };

  void walk_terrain(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < iterations; ++i) {
      random_walk();

      if (THIS_FEATURE) {
        delete THIS_TERRAIN;
        THIS_TERRAIN = nullptr;
      }

      if (THIS_TERRAIN) {
        delete THIS_TERRAIN;
        THIS_TERRAIN = nullptr;
      }
      THIS_TERRAIN = new T{this->x, this->y};
    }
    patch_holes();
  };

  void walk_feature(int x, int y) {
    this->x = x;
    this->y = y;
    for (int i = 0; i < iterations; ++i) {
      random_walk();

      if (THIS_FEATURE) {
        delete THIS_TERRAIN;
        THIS_TERRAIN = nullptr;
      }

      if (THIS_TERRAIN) {
        delete THIS_TERRAIN;
        THIS_TERRAIN = nullptr;
      }
      THIS_FEATURE = new T{this->x, this->y};
    }
    patch_holes();
  };

private:
  void random_walk() {
    int x_dir = rand() % 3 - 1; // 0,1,2 gives -1,0,1
    int y_dir = rand() % 3 - 1;

    int proposed_x = this->x + x_dir;
    int proposed_y = this->y + y_dir;

    if (0 <= proposed_x && proposed_x <= limit)
      x = proposed_x;
    if (0 <= proposed_y && proposed_y <= limit)
      y = proposed_y;
  };

  void patch_holes() {
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        if (terrain[i][j] == nullptr) {
          terrain[i][j] = new Dirt{i, j};
        }
      }
    }
  }
  int x{SIZE / 2};
  int y{SIZE / 2}; // position

  Terrain *(&terrain)[SIZE][SIZE];
  Feature *(&feature)[SIZE][SIZE];

  int iterations;

  int limit = SIZE;
  unsigned int seed;
};
