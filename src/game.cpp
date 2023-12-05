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
  // printf("valid coords\n");
  bool non_existant_feature = (features->get(proposed_x, proposed_y) == nullptr);
  bool can_walk = non_existant_feature;
  if (!non_existant_feature)
  {
    can_walk = features->get(proposed_x, proposed_y)->get_walkable();
    // printf("feature walk status: %i\n", can_walk);
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
    pathfind(get_agent(agent.second->posX, agent.second->posY));

    int i = agent.second->posX;
    int j = agent.second->posY;
    pointer_feature feat = std::move(get_feature(i, j));
    feat->consume();
    set_feature(i, j, feat);
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
  int a_i = agent->posX;
  int a_j = agent->posY;

  int max_i = a_i;
  int max_j = a_j;
  int max_l = features->get(max_i, max_j)->get_level();

  int kernel[2*agent->visionRange + 1][2*agent->visionRange + 1]; // column, row
  for (int i = 0; i <= 2*agent->visionRange; i++)
  {
    for (int j = 0; j <= 2*agent->visionRange; j++)
    {
      int proposed_x = a_i - agent->visionRange + i;
      int proposed_y = a_j - agent->visionRange + j;
      
      if (proposed_x >= SIZE || proposed_x <= 0 || proposed_y >= SIZE ||
      proposed_y <= 0)
        kernel[i][j] = -1;
      else if (!terrain->get(proposed_x, proposed_y)->get_walkable())
        kernel[i][j] = -2;
      else
      {
        kernel[i][j] = features->get(proposed_x, proposed_y)->get_level();
        int modifier = mt() % 10;
        // printf("feature level: %i\n", kernel[i][j]);
        if (kernel[i][j] + modifier > max_l)
        {
          max_i = proposed_x;
          max_j = proposed_y;
          max_l = kernel[i][j] + modifier;
        }
      }
    }
  }
  // Dir random_proposed{static_cast<int>(mt())};
  // random_proposed.set_x(agent->posX + random_proposed.get_x());
  // random_proposed.set_y(agent->posY + random_proposed.get_y());

  if (max_i > a_i)
    max_i = a_i + 1;
  else if (max_i < a_i)
    max_i = a_i - 1;

  if (max_j > a_j)
    max_j = a_j + 1;
  else if (max_j < a_j)
    max_j = a_j - 1;

  Dir proposed{max_i, max_j};
  if (agent->id == 1)
  {
    printf("cur pos: %i, %i\n", a_i, a_j);
    for (int j = 0; j <= 2*agent->visionRange; j++)
    {
      for (int i = 0; i <= 2*agent->visionRange; i++)
      {
        printf("%i ", kernel[i][j]);
      }
      printf("\n");
    }
    printf("proposed pos: %i, %i\n", proposed.get_x(), proposed.get_y());
  }

  bool valid = check_move(proposed);
  if (valid) {
    agent->move_agent(proposed.get_x(), proposed.get_y());
  };

  set_agent(agent->posX, agent->posY, agent);
};
