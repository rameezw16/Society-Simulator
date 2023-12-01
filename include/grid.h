#pragma once
#include "./size.h"

template <typename T> class Grid {
public:
  Grid() {
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        grid[i][j] = nullptr;
      }
    }
  };

  ~Grid() {
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        delete grid[i][j];
        grid[i][j] = nullptr;
      }
    }
  }

  T *get_(int i, int j) {
    if (0 < i && i < gridsize && 0 < j && j < gridsize)
      return (grid[i][j]);
  }

  void set(int i, int j, T *pointer_to_entity) {
    if (0 < i && i < gridsize && 0 < j && j < gridsize)
      grid[i][j] = pointer_to_entity;
  }

private:
  T *grid[SIZE][SIZE]; // grid of terrain pointers, aggregation
  const int gridsize = SIZE;
};
