#include "../include/grid.h"
#include <iostream>
// SIZE is the internal grid representation

Grid::Grid(unsigned int seed)
  : perlin_gen(seed), a(static_cast<int>(seed)) { //why is "a" a mersenne twister? Have fun.
  perlin_gen.add_octave(0.3, 5);
  perlin_gen.add_octave(0.1, 5);
  perlin_gen.add_octave(0.9, 5);

  randomly_generate();
};

Grid::~Grid() {
  for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	  delete terrain[i][j];
	};
  };
};

// internal representation
void Grid::randomly_generate() {
  for (int i = 0; i < SIZE; i++) {
	for (int j = 0; j < SIZE; j++) {
	  double noise = perlin_gen.get_noise(i, j);
	  int selection = (int)(noise * 10) % 3;
	  switch (selection) {
	  case 1:
		terrain[i][j] = new Dirt {i, j};
		feature[i][j] = nullptr; //new Grass {i, j};
		//agent[i][j] = nullptr;
		break;
	  case 0:
		terrain[i][j] = new Dirt{i, j};
		feature[i][j] = new Wall {i,j}; 
		//agent[i][j] = nullptr;
		break;
	  case 2:
		terrain[i][j] = new Dirt{i, j};
		feature[i][j] = nullptr; 
		//agent[i][j] = nullptr;	// 
		break;
	  };
    };
  };
  //do random walk and break features


  unsigned int seed = (unsigned int)(perlin_gen.get_noise(10,10) * 10);

  Random_Walker random_walker {SIZE, seed};

  const int middle = SIZE/2;

  const int total_iters = 500;


  random_walker.destructive_walk(middle, middle, &feature, 500);
  random_walker.destructive_walk(middle, middle, &feature, 500);
  random_walker.destructive_walk(middle, middle, &feature, 500);

  random_walker.creative_walk_fauna(middle,middle,&feature,total_iters);
  random_walker.creative_walk_water(middle,middle,&terrain,total_iters * 3);

  random_walker.creative_walk_water(0,0,&terrain,total_iters);
  random_walker.creative_walk_water(SIZE,0,&terrain,total_iters);
  random_walker.creative_walk_water(middle,middle,&terrain,total_iters);
  random_walker.creative_walk_water(0,SIZE,&terrain,total_iters);
  random_walker.creative_walk_water(SIZE,SIZE,&terrain,total_iters);

  random_walker.creative_walk_fauna(0,0,&feature,total_iters);
  random_walker.creative_walk_fauna(SIZE,0,&feature,total_iters);
  random_walker.creative_walk_fauna(0,SIZE,&feature,total_iters);
  random_walker.creative_walk_fauna(SIZE,SIZE,&feature,total_iters);

  //agent[middle][middle] = new Wolf {middle + 10, middle};
  add_people_to_grid();
};


void Grid::add_people_to_grid() {
  for (int i = 0; i < 10; i ++) {
	for (int j = 0; j < 10; j++) {
	  agent[i][j] = new Agent{this->a,0,0,"abc",30,30};
	};
  };
};


bool Grid::check_move(Agent &a, Dir direction) {
  int proposed_x = a.posX + direction.get_x(); 
  int proposed_y = a.posY + direction.get_y(); 

  return (!terrain[proposed_x][proposed_y] && !feature[proposed_x][proposed_y]); //can move with to place with no terrain and features
};

void Grid::pathfind(Agent &a) {
};







