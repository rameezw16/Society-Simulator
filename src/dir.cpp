#include "../include/dir.h"

Dir::Dir(int x, int y) : x(x), y(y) {};

Dir::Dir() {
  set_x(rand() % 3-1);
  set_x(rand() % 3-1);
  
}

int Dir::get_x() const {return this->x;};
int Dir::get_y() const {return this->y;};

void Dir::set_x(int x) {this->x = x;};
void Dir::set_y(int y) {this->y = y;};






