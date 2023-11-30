#pragma once
#include <random>
#include <ctime>

class Dir {
public:
  Dir(int seed); //just calling it like this will make it generate randomly

  Dir(int x, int y);

  int get_x() const;
  int get_y() const;

  void set_x(int x);
  void set_y(int y);

  
private:
  int x, y {};

};
