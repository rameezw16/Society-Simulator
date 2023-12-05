#include "../include/game.h"
// SIZE is the internal grid representation

Game::Game(unsigned int seed) : mt(static_cast<int>(seed)) {
  Earth_builder generator{mt, seed};
  generator.general_generation();
  generator.random_walk_generation();
  generator.add_people_to_grid();

  terrain = std::move(generator.get_terrain());
  features = std::move(generator.get_features());
  agents = std::move(generator.get_agents());
  
};

pointer_terrain &Game::get_terrain(int i, int j) const {
  return (terrain->get(i, j));
}

pointer_feature &Game::get_feature(int i, int j) const {
  return (features->get(i, j));
}

pointer_agent &Game::get_agent(int i, int j) const {
  return (agents->get(i, j));
}

void Game::set_terrain(int i, int j, pointer_terrain &val) {
  terrain->set(i, j, val);
}
void Game::set_feature(int i, int j, pointer_feature &val) {
  features->set(i, j, val);
}
void Game::set_agent(int i, int j, pointer_agent &val) {
  agents->set(i, j, val);
}

Game::~Game(){};

// void Game::add_people_to_grid() {
//   for (int i = 0; i < SIZE; i++) {
//     for (int j = 0; j < SIZE; j++) {
//       if (get_feature(i, j) == nullptr && (get_terrain(i, j)->get_walkable() == true)
//       &&
//           (mt() % 200 == 1))
//           new Agent{this->mt, 0, 0, "abc", i, j};
//     };
//   };
// };

bool Game::check_move(Dir direction) {
  int proposed_x = direction.get_x();
  int proposed_y = direction.get_y();
  if (proposed_x >= SIZE || proposed_x <= 0 || proposed_y >= SIZE ||
      proposed_y <= 0)
    return false;
  printf("valid coords\n");
  bool non_existant_feature = (features->get(proposed_x, proposed_y) == nullptr);
  bool can_walk = non_existant_feature;
  if (!non_existant_feature)
  {
    can_walk = features->get(proposed_x, proposed_y)->get_walkable();
    printf("feature walk status: %i\n", can_walk);
  }


  return (terrain->get(proposed_x, proposed_y)->get_walkable() &&
          can_walk); // can move with to place with no
                     // terrain and features
};

void Game::step() {
  this->features->update(); // update all grass
  Grass::step_season(); // update overall season
  for (std::pair<int, Agent*> agent : Agent::AgentList)
  {
    int i = agent.second->posX;
    int j = agent.second->posY;
    pointer_feature terr = std::move(get_feature(i, j));
    terr->consume();
    set_feature(i, j, terr);
    pathfind(get_agent(i, j));
  }
  // for (int i = 0; i < SIZE; ++i) {
  //   for (int j = 0; j < SIZE; ++j) {
  //     if (get_agent(i, j) != nullptr) {
  //       unique_ptr<Grass> t;
  //       set_agent(i, j, pathfind(get_agent(i, j)));
  //     }
  //   }
  // }
};

void Game::pathfind(pointer_agent& agent) 
{

  Dir random_proposed{static_cast<int>(mt())};
  random_proposed.set_x(agent->posX + random_proposed.get_x());
  random_proposed.set_y(agent->posY + random_proposed.get_y());

  bool valid = check_move(random_proposed);
  if (valid) {
    agent->move_agent(random_proposed.get_x(), random_proposed.get_y());
  };

  set_agent(agent->posX, agent->posY, agent);
};
