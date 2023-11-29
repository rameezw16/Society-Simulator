#pragma once
#include "./features/feature.h"
#include "./perlin.h"
#include "./terrain/terrain.h"
#include "./terrain/water.h"
#include "./terrain/dirt.h"
#include "./features/grass.h"
#include "./features/wall.h"
#include "./randomwalker.h"
#include "./characters/actor.h"
#include "./size.h"
#include "./dir.h"
#include <SDL2/SDL.h>
#include <random>


// We will now make a grid of entities, this contains a spritesheet

class Grid {
public:
  Grid(unsigned int seed = 1985);
  ~Grid();

  void randomly_generate();
  void random_walk(int x, int y);
  void add_people_to_grid();

  //making this public just for testing
  
  bool check_move(Agent *a, Dir direction);

  void step();
  void pathfind(Agent *a);

  Terrain *terrain[SIZE][SIZE]; // grid of terrain pointers, aggregation
  Feature *feature[SIZE][SIZE]; // grid of features built on terrain
  Agent *agent[SIZE][SIZE];   // grid of entities located on terrain
  //Agent list in Agent class

private:
<<<<<<< HEAD
  Perlin erlin_gen;
  std::mt19937 mt; 

  Interaction_Manager* interaction_manager;
=======
  Perlin perlin_gen;
  std::mt19937 mt; 

  const int gridsize = SIZE;
};
