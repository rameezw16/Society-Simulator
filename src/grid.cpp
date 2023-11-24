#include "../include/grid.h"
#include <iostream>
// 60 is the internal grid representation

Grid::Grid(unsigned int seed)
	: perlin_gen(seed), temperature(seed), humidity(seed), evil(seed), random_walker(30,30,60,seed) {
  perlin_gen.add_octave(0.3, 5);
  perlin_gen.add_octave(0.1, 5);

  // I want highly varying temperatures and humidities
  temperature.add_octave(1.0, 5);
  humidity.add_octave(1.0, 9);
  evil.add_octave(0.5, 3);

  randomly_generate();
};

Grid::~Grid() {
  for (int i = 0; i < 60; i++) {
	for (int j = 0; j < 60; j++) {
	  delete terrain[i][j];
	};
  };
};

// internal representation
void Grid::randomly_generate() {
  for (int i = 0; i < 60; i++) {
	for (int j = 0; j < 60; j++) {
	  double noise = perlin_gen.get_noise(i * 10, j * 10);
	  int selection = (int)(noise * 10) % 3;
	  switch (selection) {
	  case 1:
		terrain[i][j] = new Water{i, j};
		feature[i][j] = nullptr;
		character[i][j] = nullptr;
		break;
	  case 0:
		terrain[i][j] = new Dirt{i, j};
		feature[i][j] = nullptr; 
		character[i][j] = nullptr;
		break;
	  case 2:
		terrain[i][j] = new Dirt{i, j};
		feature[i][j] = nullptr; 
		character[i][j] = nullptr;
		break;
	  };
    };
  };
  //do random walk and break features

  const int total_iters = 500;

  unsigned int seed = (unsigned int)(perlin_gen.get_noise(10,10) * 10);
  Random_Walker rw1 {30,30, 60, seed};
  Random_Walker rw2 {30,30, 60, seed * 3};
  Random_Walker rw3 {30,30, 60, seed * 6};
  Random_Walker rw4 {30,30, 60, seed * 3 + 9};
  Random_Walker rw5 {30,30, 60, seed * 3 % 2};

  //rw1.destructive_walk(&feature,total_iters);
  //rw2.destructive_walk(&feature,total_iters);
  //rw3.destructive_walk(&feature,total_iters);
  //rw4.destructive_walk(&feature,total_iters);
  //rw5.destructive_walk(&feature,total_iters);

  rw5.creative_walk_walls(&feature,total_iters);



};










