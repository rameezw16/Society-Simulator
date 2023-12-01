#include "../include/randomwalker.h"

Random_Walker::Random_Walker(int limit, unsigned int seed)
    : limit(limit), seed(seed) {
  srand(seed);
};

void Random_Walker::random_walk() {
  int x_dir = rand() % 3 - 1; // 0,1,2 gives -1,0,1
  int y_dir = rand() % 3 - 1;

  int proposed_x = this->x + x_dir;
  int proposed_y = this->y + y_dir;

  if (0 <= proposed_x && proposed_x <= limit)
    x = proposed_x;
  if (0 <= proposed_y && proposed_y <= limit)
    y = proposed_y;

  // std::cout << x << " " << y << " " << x_dir << " " << y_dir << "\n";
};

void Random_Walker::destructive_walk(int x, int y,
                                     Terrain *(*terrain)[SIZE][SIZE],
                                     int iterations) {
  this->x = x;
  this->y = y;

  for (int i = 0; i < iterations; i++) {
    random_walk();
    Terrain *terrain_to_be_deleted = (*terrain)[this->x][this->y];
    if (terrain_to_be_deleted->get_type() == "wall") {
      delete (*terrain)[this->x][this->y];
      (*terrain)[this->x][this->y] = nullptr;
      (*terrain)[this->x][this->y] = new Dirt{this->x, this->y};
    };
  };
};

void Random_Walker::creative_walk_walls(int x, int y,
                                        Terrain *(*terrain)[SIZE][SIZE],
                                        int iterations) {
  this->x = x;
  this->y = y;

  for (int i = 0; i < iterations; i++) {
    random_walk();
    if ((*terrain)[this->x][this->y] == nullptr)
      (*terrain)[this->x][this->y] = new Wall{this->x, this->y};
  };
};

void Random_Walker::creative_walk_fauna(int x, int y,
                                        Feature *(*feature)[SIZE][SIZE],
                                        int iterations) {
  this->x = x;
  this->y = y;

  for (int i = 0; i < iterations; i++) {
    random_walk();
    if ((*feature)[this->x][this->y] == nullptr)
      (*feature)[this->x][this->y] = new Grass{this->x, this->y, 10, 10};
    if ((*feature)[this->x][this->y]->get_type() == "water")
      std::cout << this->x << " " << this->y << "\n";
  };
};

// 2d array of pointers to entities
void Random_Walker::creative_walk_water(int x, int y,
                                        Terrain *(*terrain)[SIZE][SIZE],
                                        int iterations) {

  this->x = x;
  this->y = y;

  for (int i = 0; i < iterations; i++) {
    random_walk();

    delete (*terrain)[this->x][this->y];
    (*terrain)[this->x][this->y] = nullptr;
    (*terrain)[this->x][this->y] = new Water{this->x, this->y};
  };
};
