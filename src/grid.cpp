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
	  int selection = (int)(noise * 10) % 4;
	  switch (selection) {
	  case 0:
		terrain[i][j] = new Water{i, j};
		feature[i][j] = nullptr;
		character[i][j] = nullptr;
		break;
	  case 1:
		terrain[i][j] = new Dirt{i, j};
		feature[i][j] = new Wall{i, j};
		character[i][j] = nullptr;
		break;
	  case 2:
		terrain[i][j] = new Dirt{i, j}; 
		feature[i][j] = new Grass{i, j}; 
		character[i][j] = nullptr;
		break;
	  case 3:
		terrain[i][j] = new Dirt{i, j};
		feature[i][j] = nullptr; 
		character[i][j] = nullptr;
		break;
	  };
    };
  };

  //do random walk and break features
  Random_Walker rw1 {30,30,60, 10};
  rw1.destructive_walk(&feature,100);

};










