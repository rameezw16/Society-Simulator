#include "../include/grid.h"
#include <iostream>
// 60 is the internal grid representation

Grid::Grid(unsigned int seed)
	: perlin_gen(seed) {
  perlin_gen.add_octave(0.3, 5);
  perlin_gen.add_octave(0.1, 5);

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

  const int total_iters = 250;

  unsigned int seed = (unsigned int)(perlin_gen.get_noise(10,10) * 10);

  Random_Walker random_walker {60, seed};

  random_walker.creative_walk_walls(30,30,&feature,500);
  random_walker.creative_walk_fauna(30,30,&feature,500);

  random_walker.creative_walk_walls(0,0,&feature,total_iters);
  //random_walker.creative_walk_walls(60,0,&feature,total_iters);
  random_walker.creative_walk_walls(0,60,&feature,total_iters);
  //random_walker.creative_walk_walls(60,60,&feature,total_iters);


  //random_walker.creative_walk_fauna(0,0,&feature,total_iters);
  random_walker.creative_walk_fauna(60,0,&feature,total_iters);
  random_walker.creative_walk_fauna(0,60,&feature,total_iters);
  random_walker.creative_walk_fauna(60,60,&feature,total_iters);


  //rw1.destructive_walk(&feature,total_iters);
  //rw2.destructive_walk(&feature,total_iters);
  //rw3.destructive_walk(&feature,total_iters);
  //rw4.destructive_walk(&feature,total_iters);
  //rw5.destructive_walk(&feature,total_iters);




};










