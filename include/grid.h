#pragma once
#include "./size.h"
#include <memory>

template <typename T> class Grid {
public:
  Grid() {
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        // grid[i][j] = nullptr;
      }
    }
  };

  ~Grid() {
    // unique ptr should take care of this
    for (int i = 0; i < SIZE; ++i) {
      for (int j = 0; j < SIZE; ++j) {
        // delete grid[i][j];
        // grid[i][j] = nullptr;
      }
    }
  };

  std::unique_ptr<T> &get(int i, int j) { return (grid[i % SIZE][j % SIZE]); }

  void set(int i, int j,
           std::unique_ptr<T> &pointer_to_entity) { // takes in reference
    grid[i % 100][j % 100] = std::move(pointer_to_entity);
  }

  void reset(int i, int j) { grid[i % 100][j % 100].reset(nullptr); }

private:
  std::unique_ptr<T> grid[SIZE][SIZE]; // grid of terrain pointers, aggregation
  const int gridsize = SIZE;
};
