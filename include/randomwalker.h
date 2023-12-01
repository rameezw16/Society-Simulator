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

class Random_Walker {
public:
  Random_Walker(int limit, unsigned int seed);
  void random_walk();
  void destructive_walk(int x, int y, Terrain *(*terrain)[SIZE][SIZE],
                        Feature *(*feature)[SIZE][SIZE],
                        int iterations); // 2d array of pointers to entities
  void creative_walk_fauna(int x, int y, Terrain *(*terrain)[SIZE][SIZE],
                           Feature *(*feature)[SIZE][SIZE],
                           int iterations); // 2d array of pointers to entities

  void creative_walk_walls(int x, int y, Terrain *(*terrain)[SIZE][SIZE],
                           Feature *(*feature)[SIZE][SIZE],
                           int iterations); // 2d array of pointers to entities
  void creative_walk_water(int x, int y, Terrain *(*terrain)[SIZE][SIZE],
                           Feature *(*feature)[SIZE][SIZE],
                           int iterations); // 2d array of pointers to entities

private:
  int x{SIZE / 2};
  int y{SIZE / 2}; // position

  int limit;
  unsigned int seed;
};
