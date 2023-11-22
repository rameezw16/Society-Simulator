#include "../include/grid.h"
// 60 is the internal grid representation

Grid::Grid(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture,
		   Spritesheet *spritesheet, unsigned int seed)
	: window(window), renderer(renderer), texture(texture),
	  spritesheet(spritesheet), perlin_gen(seed), temperature(seed),
	  humidity(seed), evil(seed) {
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
	  case 0:
		terrain[i][j] = new Water{i, j};
		break;
	  case 1:
		terrain[i][j] = new Dirt{i, j};
		break;
	  case 2:
		terrain[i][j] = new Grass{i, j}; //this needs to go back to wall. 
		break;
	  }
	};
  };
};

void Grid::draw_grid() {
  // SDL_RenderPresent(this->renderer);

  for (int i = 0; i < 60; i++) {
	for (int j = 0; j < 60; j++) {
	  terrain[i][j]->draw(spritesheet, texture);
	  // SDL_RenderPresent(this->renderer);
    };
  };
};
