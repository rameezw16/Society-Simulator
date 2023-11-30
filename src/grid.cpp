#include "../include/grid.h"
#include <iostream>
// SIZE is the internal grid representation

Grid::Grid(unsigned int seed) : perlin_gen(seed), food(seed), mt(static_cast<int>(seed)) {
  perlin_gen.add_octave(0.1, 5);
  perlin_gen.add_octave(0.9, 5);


  food.add_octave(0.3,5);

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
      int selection = (int)(noise * 10) % 5;
      switch (selection) {
      case 1:
        terrain[i][j] = new Dirt{i, j, 13, 24}; //13 and 24 for bright dirt
        feature[i][j] = nullptr; // new Grass {i, j};
        agent[i][j] = nullptr;
        break;
      case 0:
        terrain[i][j] = new Wall{i, j};
        feature[i][j] = nullptr;
        agent[i][j] = nullptr;
        break;
      default:
        terrain[i][j] = new Dirt{i, j};
        feature[i][j] = nullptr;
        agent[i][j] = nullptr;	//
        break;
      };
    };
  };

  unsigned int seed = (unsigned int)(perlin_gen.get_noise(10, 10) * 10);
  Random_Walker random_walker{SIZE, seed};
  const int middle = SIZE / 2;
  const int total_iters = 500;

  //destroy things
  random_walker.destructive_walk(middle, middle, &terrain, 500);
  random_walker.destructive_walk(middle, middle, &terrain, 500);
  random_walker.destructive_walk(middle, middle, &terrain, 500);

  //add features
  random_walker.creative_walk_fauna(middle, middle, &feature, total_iters);
  random_walker.creative_walk_fauna(0, 0, &feature, total_iters);
  random_walker.creative_walk_fauna(SIZE, 0, &feature, total_iters);
  random_walker.creative_walk_fauna(0, SIZE, &feature, total_iters);
  random_walker.creative_walk_fauna(SIZE, SIZE, &feature, total_iters);

  //add water
  random_walker.creative_walk_water(middle, middle, &terrain, total_iters * 3);
  random_walker.creative_walk_water(0, 0, &terrain, total_iters);
  random_walker.creative_walk_water(SIZE, 0, &terrain, total_iters);
  random_walker.creative_walk_water(middle, middle, &terrain, total_iters);
  random_walker.creative_walk_water(0, SIZE, &terrain, total_iters);
  random_walker.creative_walk_water(SIZE, SIZE, &terrain, total_iters);


  add_people_to_grid();
};

void Grid::add_people_to_grid() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      if (feature[i][j] == nullptr && (terrain[i][j]->get_walkable() == false) && (mt() % 200 == 1))
        agent[i][j] = new Agent{this->mt, 0, 0, "abc", i, j};
    };
  };
};

bool Grid::check_move(Agent *a, Dir direction) {
  int proposed_x = direction.get_x();
  int proposed_y = direction.get_y();
  if (proposed_x >= SIZE || proposed_x <= 0 || proposed_y >= SIZE || proposed_y <= 0) return false;
  bool non_existant_feature = (feature[proposed_x][proposed_y] == nullptr);
  bool can_walk = non_existant_feature;
  if (!non_existant_feature) can_walk = feature[proposed_x][proposed_y]->get_walkable();


  return (terrain[proposed_x][proposed_y]->get_walkable() && can_walk); // can move with to place with no
                                             // terrain and features
};

void Grid::step() {

  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      if (agent[i][j] != nullptr) {
        pathfind(agent[i][j]);
      }

      if (feature[i][j] != nullptr) {
        feature[i][j]->step();
      }
    }
  }

};

void Grid::pathfind(Agent *a) {

  Dir random_proposed{static_cast<int>(mt())}; // empty constructor makes it generate
                         // randomly

  random_proposed.set_x(a->posX + random_proposed.get_x());
  random_proposed.set_y(a->posY + random_proposed.get_y());

  bool valid = check_move(a, random_proposed);
  if (valid) {a->move_agent(random_proposed.get_x(), random_proposed.get_y());};
};
