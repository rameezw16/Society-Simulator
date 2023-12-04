#include "../include/game.h"
// SIZE is the internal grid representation

Game::Game(unsigned int seed) : mt(static_cast<int>(seed)) {
  Earth_builder generator{seed};
  generator.general_generation();
  generator.random_walk_generation();

  terrain = std::move(generator.get_terrain());
  features = std::move(generator.get_features());
};

pointer_terrain &Game::get_terrain(int i, int j) const {
  return (terrain->get(i, j));
}

pointer_feature &Game::get_feature(int i, int j) const {
  return (features->get(i, j));
}

void Game::set_terrain(int i, int j, pointer_terrain &val) {
  terrain->set(i, j, val);
}
void Game::set_feature(int i, int j, pointer_feature &val) {
  features->set(i, j, val);
}

Game::~Game(){};

// void Game::add_people_to_grid() {
//   for (int i = 0; i < SIZE; i++) {
//     for (int j = 0; j < SIZE; j++) {
//       if (feature[i][j] == nullptr && (terrain[i][j]->get_walkable() == true)
//       &&
//           (mt() % 200 == 1))
//         agent[i][j] = new Agent{this->mt, 0, 0, "abc", i, j};
//     };
//   };
// };

// bool Game::check_move(Agent *a, Dir direction) {
//   int proposed_x = direction.get_x();
//   int proposed_y = direction.get_y();
//   if (proposed_x >= SIZE || proposed_x <= 0 || proposed_y >= SIZE ||
//       proposed_y <= 0)
//     return false;
//   bool non_existant_feature = (feature[proposed_x][proposed_y] == nullptr);
//   bool can_walk = non_existant_feature;
//   if (!non_existant_feature)
//     can_walk = feature[proposed_x][proposed_y]->get_walkable();

//   return (terrain[proposed_x][proposed_y]->get_walkable() &&
//           can_walk); // can move with to place with no
//                      // terrain and features
// };

void Game::step() {
  this->features->update();
  Grass::step_season();
  for (int i = 0; i < SIZE; ++i) {
    for (int j = 0; j < SIZE; ++j) {
      // if (agent[i][j] != nullptr) {
      //   pathfind(agent[i][j]);
      // }
    }
  }
};

// void Game::pathfind(Agent *a) {

//   Dir random_proposed{static_cast<int>(mt())};
//   random_proposed.set_x(a->posX + random_proposed.get_x());
//   random_proposed.set_y(a->posY + random_proposed.get_y());

//   bool valid = check_move(a, random_proposed);
//   if (valid) {
//     a->move_agent(random_proposed.get_x(), random_proposed.get_y());
//   };
// };
