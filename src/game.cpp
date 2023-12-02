#include "../include/game.h"
// SIZE is the internal grid representation

Game::Game(unsigned int seed) : mt(static_cast<int>(seed)) {
  Earth_builder perlin_builder{seed};
  perlin_builder.general_generation();

  terrain = std::move(perlin_builder.get_terrain());
  features = std::move(perlin_builder.get_features());
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

// internal representation
// void Game::randomly_generate() {
//   for (int i = 0; i < SIZE; i++) {
//     for (int j = 0; j < SIZE; j++) {
//       double noise = perlin_gen.get_noise(i, j);
//       int selection = (int)(noise * 10) % 5;
//       switch (selection) {
//       case 1:
//         terrain[i][j] = new Dirt{i, j, 13, 24}; // 13 and 24 for bright dirt
//         feature[i][j] = nullptr;                // new Grass {i, j};
//         agent[i][j] = nullptr;
//         break;
//       case 0:
//         terrain[i][j] = new Wall{i, j};
//         feature[i][j] = nullptr;
//         agent[i][j] = nullptr;
//         break;
//       default:
//         terrain[i][j] = new Dirt{i, j};
//         feature[i][j] = nullptr;
//         agent[i][j] = nullptr; //
//         break;
//       };
//     };
//   };
// };

// void Game::create_walls() {
//   unsigned int seed = (unsigned int)(perlin_gen.get_noise(10, 10) * 10);
//   Random_Walker<Wall> wall_replace{seed, terrain, feature};
//   wall_replace.walk_terrain(SIZE - 3, SIZE - 3);
//   wall_replace.walk_terrain(0, 0);
// };

// void Game::create_water() {
//   unsigned int seed = (unsigned int)(perlin_gen.get_noise(20, 20) * 10);
//   Random_Walker<Water> water_replace{seed, terrain, feature, 500};
//   water_replace.walk_terrain(0, 0);
//   water_replace.walk_terrain(SIZE - 3, SIZE - 3);
// }

// void Game::create_fauna() {
//   // add features
//   unsigned int seed = (unsigned int)(perlin_gen.get_noise(30, 30) * 10);
//   Random_Walker<Grass> grass_replace{seed, terrain, feature, 500};
//   grass_replace.walk_feature(0, 0);
//   grass_replace.walk_feature(SIZE - 3, SIZE - 3);
// }

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

// void Game::step() {
//   for (int i = 0; i < SIZE; ++i) {
//     for (int j = 0; j < SIZE; ++j) {
//       if (agent[i][j] != nullptr) {
//         pathfind(agent[i][j]);
//       }

//       if (feature[i][j] != nullptr) {
//         std::cout << feature[i][j]->get_type() << "\n";
//         feature[i][j]->consume();
//         feature[i][j]->step();
//       }
//     }
//   }
// };

// void Game::pathfind(Agent *a) {

//   Dir random_proposed{static_cast<int>(mt())};
//   random_proposed.set_x(a->posX + random_proposed.get_x());
//   random_proposed.set_y(a->posY + random_proposed.get_y());

//   bool valid = check_move(a, random_proposed);
//   if (valid) {
//     a->move_agent(random_proposed.get_x(), random_proposed.get_y());
//   };
// };
