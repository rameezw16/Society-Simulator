#include "../include/randomwalker.h"

Random_Walker::Random_Walker(int x, int y, int limit, unsigned int seed) : x(x), y(y), limit(limit), seed(seed) {srand(seed);};

void Random_Walker::random_walk() {
  int x_dir = rand() % 3 - 1; //0,1,2 gives -1,0,1
  int y_dir = rand() % 3 - 1;

  int proposed_x = x + x_dir ;
  int proposed_y = y + y_dir ;

  if (0 < proposed_x && proposed_x < limit) x = proposed_x;
  if (0 < proposed_y && proposed_y < limit) y = proposed_y;

  //std::cout << x << " " << y <<  " " << x_dir << " " << y_dir << "\n";
};

void Random_Walker::destructive_walk(Feature *(*feature)[60][60],
									 int iterations) {

  for (int i = 0; i < iterations; i++) {
		random_walk();
		Entity *feature_to_be_deleted = (*feature)[x][y];
		if (feature_to_be_deleted != nullptr) {
		  delete (*feature)[x][y];
		  (*feature)[x][y] = nullptr;
        };
  };
};


void Random_Walker::creative_walk_walls(Feature *(*feature)[60][60],
									 int iterations) {

  for (int i = 0; i < iterations; i++) {
		random_walk();
		Entity *feature_to_be_added = (*feature)[x][y];
		(*feature)[x][y] = new Wall{x, y};
  };
};





int Random_Walker::get_x() {
  return x;
};
  
int Random_Walker::get_y() {
  return y;
};
