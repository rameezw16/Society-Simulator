#include "../include/randomwalker.h"

Random_Walker::Random_Walker(int x, int y, int limit, unsigned int seed)
    : x(x), y(y), limit(limit), perlin_gen(seed) {
  perlin_gen.add_octave(1.0,5);
};

void Random_Walker::random_walk() {
  //No particular reason why x,y and y,x are switched, just for better randomness, I guess
  int x_dir = 1; //(int)(perlin_gen.get_noise(x,y) * 10) % 2; // there are four directions we can go in
  int y_dir = 1; //(int)(perlin_gen.get_noise(x,y) * 10) % 2;

  int proposed_x = x + x_dir - 1;
  int proposed_y = y + y_dir - 1;

  if ((set_x.find(proposed_x) == set_x.end() && proposed_x < limit &&
	   proposed_x > 0)) { // if it is a new value, go for it
	x = proposed_x;       // we currently have 0,1 and we want -1, 1
	set_x.insert(x);
  };

  if ((set_y.find(proposed_y) == set_y.end() && proposed_y < limit &&
	   proposed_y > 0)) { // if it is a new value, go for it
	y = proposed_y;       // we currently have 0,1 and we want -1, 1
	set_y.insert(y);
  };

  std::cout << x << " " << y << "\n";
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

int Random_Walker::get_x() {
  return x;
};
  
int Random_Walker::get_y() {
  return y;
};
