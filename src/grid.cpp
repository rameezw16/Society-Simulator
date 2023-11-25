#include "../include/grid.h"
#include <iostream>
// SIZE is the internal grid representation

<<<<<<< HEAD
Grid::Grid(unsigned int seed) : perlin_gen(seed), mt(seed) {
=======
Grid::Grid(unsigned int seed)
	: perlin_gen(seed) {
>>>>>>> parent of 8a893ed (Made the interaction manager part of the grid, added walkable param)
  perlin_gen.add_octave(0.3, 5);
  perlin_gen.add_octave(0.1, 5);
  // perlin_gen.add_octave(0.4, 5);

  randomly_generate();
};

Grid::~Grid() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      delete terrain[i][j];
    };
  };
};

<<<<<<< HEAD
void Grid::perlin_generation() {
=======
// internal representation
void Grid::randomly_generate() {
>>>>>>> parent of 8a893ed (Made the interaction manager part of the grid, added walkable param)
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      double noise = perlin_gen.get_noise(i, j);
      int selection = (int)(noise * 10) % 3;
      switch (selection) {
      case 1:
        terrain[i][j] = new Dirt{i, j};
        feature[i][j] = nullptr; // new Grass {i, j};
        agent[i][j] = nullptr;
        break;
      case 0:
        terrain[i][j] = new Dirt{i, j};
        feature[i][j] = new Wall{i, j};
        agent[i][j] = nullptr;
        break;
      case 2:
        terrain[i][j] = new Dirt{i, j};
        feature[i][j] = nullptr;
        agent[i][j] = nullptr;
        break;
      };
    };
  };
};

<<<<<<< HEAD
void Grid::random_walk_generation() {

  unsigned int seed = (unsigned int)(perlin_gen.get_noise(10, 10) * 10);
=======
>>>>>>> parent of 8a893ed (Made the interaction manager part of the grid, added walkable param)

  Random_Walker random_walker{SIZE, seed};

  const int middle = SIZE / 2;

  const int total_iters = 500;


  random_walker.destructive_walk(middle, middle, &feature, 500);
  random_walker.destructive_walk(middle, middle, &feature, 500);
  random_walker.destructive_walk(middle, middle, &feature, 500);

  random_walker.creative_walk_fauna(middle, middle, &feature, total_iters);
  random_walker.creative_walk_water(middle, middle, &terrain, total_iters * 3);

  random_walker.creative_walk_water(0, 0, &terrain, total_iters);
  random_walker.creative_walk_water(SIZE, 0, &terrain, total_iters);
  random_walker.creative_walk_water(middle, middle, &terrain, total_iters);
  random_walker.creative_walk_water(0, SIZE, &terrain, total_iters);
  random_walker.creative_walk_water(SIZE, SIZE, &terrain, total_iters);

<<<<<<< HEAD
  random_walker.creative_walk_fauna(0, 0, &feature, total_iters);
  random_walker.creative_walk_fauna(SIZE, 0, &feature, total_iters);
  random_walker.creative_walk_fauna(0, SIZE, &feature, total_iters);
  random_walker.creative_walk_fauna(SIZE, SIZE, &feature, total_iters);
};

void Grid::seed_people() {

  for (int i = 0; i < 10; i++) // allocate
    new Agent{mt};

  for (std::pair<int, Agent *> iter_agent :
       Agent::AgentList) { // put into internal representation
    agent[iter_agent.second->posX][iter_agent.second->posY] = iter_agent.second;
  };
};

void Grid::step() {

  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
    };
  };
};
=======
  //agent[middle][middle] = new Wolf {middle + 10, middle};




};










>>>>>>> parent of 8a893ed (Made the interaction manager part of the grid, added walkable param)
