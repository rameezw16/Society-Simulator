#pragma once
#include "./features/feature.h"
#include "./features/wall.h"
#include <random>
#include <set>
#include <iostream>



class Random_Walker {
public:
  Random_Walker(int x, int y, int limit, unsigned int seed);
  void random_walk();
  void destructive_walk(Feature* (*feature)[60][60], int iterations); //2d array of pointers to entities 
  void creative_walk_walls(Feature* (*feature)[60][60], int iterations); //2d array of pointers to entities 
  int get_x();
  int get_y();

private:
  int x, y; //position
  std::set<int> set_x;
  std::set<int> set_y;
  
  int limit;
  unsigned int seed;
};





