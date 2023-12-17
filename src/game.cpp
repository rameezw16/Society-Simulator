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
  if (proposed_x >= SIZE || proposed_x < 0 || proposed_y >= SIZE ||
      proposed_y < 0 || agents->get(proposed_x, proposed_y))
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

void Game::grow_water()
{
  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      if (this->terrain->get(i, j)->get_type() == "dirt")
      {
        int count_water_neighbours {0};
        for (int xOff = -1; xOff <= 1; ++xOff)
        {
          for (int yOff = -1; yOff <= 1; ++yOff)
          {
            if (i+xOff >= 0 && i + xOff < SIZE && j+yOff >= 0 && j+yOff < SIZE && this->terrain->get(i+xOff, j+yOff)
            && this->terrain->get(i+xOff, j+yOff)->get_type() == "water")
            {
              ++count_water_neighbours;
            }
          }
          // printf("test\n");
        }
        if (((this->mt() % 8) + 1) < count_water_neighbours) // at least 2 water neighbours
        {
          // printf("something isnt working\n");
          // printf("water neighbours: %i\n", count_water_neighbours);
          pointer_terrain new_water = std::make_unique<Water>(i, j);
          terrain->set(i, j, new_water);
        }
      }
    }
  }
}

void Game::shrink_water()
{
  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = 0; j < SIZE; ++j)
    {
      if (this->terrain->get(i, j)->get_type() == "water")
      {
        int count_dirt_neighbours {0};
        for (int xOff = -1; xOff <= 1; ++xOff)
        {
          for (int yOff = -1; yOff <= 1; ++yOff)
          {
            // printf("neighbouring type: %s\n", this->terrain->get(i, j)->get_type().c_str());
            if (i+xOff >= 0 && i + xOff < SIZE && j+yOff >= 0 && j+yOff < SIZE
            && this->terrain->get(i+xOff, j+yOff)->get_type() == "dirt")
            {
              ++count_dirt_neighbours;
            }
          }
        }
        // printf("dirt neighbours: %i\n", count_dirt_neighbours);
        if (((this->mt() % 8) + 1) < count_dirt_neighbours) // at least 2 dirt neighbour
        {
          // printf("dirt neighbours: %i\n", count_dirt_neighbours);
          pointer_terrain new_dirt = std::make_unique<Dirt>(i, j);
          terrain->set(i, j, new_dirt);

        }
      }
    }
  }
}

void Game::step() {
  // this->terrain->update(); // update all water
  if (Entity::season == Monsoon)
    grow_water();
  else if (Entity::season == Drought)
    shrink_water();
  this->features->update(); // update all grass
  Entity::step_season(); // update overall season
  std::vector<Agent*> myAgents;
  
  for (std::pair<int, Agent*> agent : Agent::AgentList)
    myAgents.push_back(agent.second);

  for (Agent* agent : myAgents)
  {  
    pathfind(get_agent(agent->posX, agent->posY));

    int i = agent->posX;
    int j = agent->posY;
    pointer_feature feat = std::move(get_feature(i, j));
    // if (features->get())
    if (feat->get_level() > 10)
    {
      feat->consume();
      agents->get(i, j)->consume();
      if (check_move({i+1, j}))
      {
        if (agents->get(i, j)->attempt_reproduce())
        {
            pointer_agent new_agent = std::make_unique<Agent>(this->mt, 0, 0, "abc", i+1, j);
            agents->set(i+1, j, new_agent);
        }
      }
      // printf("agent health: %i happ: %i, wealth: %i\n", agents->get(i, j)->aStats->health, agents->get(i, j)->aStats->happiness, agents->get(i, j)->aStats->wealth);
    }
    else
    {
      // agents->get(i, j)->
      agents->get(i, j)->decay();
      if (agents->get(i, j)->is_dead())
      {
        pointer_agent& a = get_agent(i, j);
        a.reset(); 
      }
    }
      // delete agents->get(i, j);
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

void Game::pathfind(pointer_agent& agent) // check my vision range for greatest vegetation
{
  int a_i = agent->posX;
  int a_j = agent->posY;

  int max_i = a_i;
  int max_j = a_j;
  int max_l = features->get(max_i, max_j)->get_level();

  int kernel[2*agent->vision_range + 1][2*agent->vision_range + 1];
  for (int i = 0; i <= 2*agent->vision_range; i++)
  {
    for (int j = 0; j <= 2*agent->vision_range; j++)
    {
      int proposed_x = a_i - agent->vision_range + i;
      int proposed_y = a_j - agent->vision_range + j;
      
      if (proposed_x >= SIZE || proposed_x < 0 || proposed_y > SIZE ||
      proposed_y < 0)
        kernel[i][j] = -1;
      else if (!terrain->get(proposed_x, proposed_y)->get_walkable())
      {
        kernel[i][j] = -2;
      }
      else if (agents->get(proposed_x, proposed_y))
        kernel[i][j] = -3;
      else
      {
        int modifier = mt() % 10;
        kernel[i][j] = features->get(proposed_x, proposed_y)->get_level() + modifier;
        // printf("feature level: %i\n", kernel[i][j]);
        if (kernel[i][j] > max_l)
        {
          max_i = a_i - agent->vision_range + i;
          max_j = a_j - agent->vision_range + j;
          max_l = kernel[i][j];
        }

      }
    }
  }

  // printf("max before love: %i\n", max_l);

  int social_kernel_size = (2*agent->social_circle+1)/(2*agent->vision_range+1);
  for (int i = 0; i < 2*agent->vision_range+1; ++i)
  {
    for (int j = 0; j < 2*agent->vision_range+1; ++j)
    {
      int love_val = 0;
      int agent_count = 0;
      for (int a = 0; a < social_kernel_size; ++a)
      {
        for (int b = 0; b < social_kernel_size; ++b)
        {
          int check_x = a_i - agent->social_circle + i*social_kernel_size + a;
          int check_y = a_j - agent->social_circle + j*social_kernel_size + b;
          if (check_x >= SIZE || check_x < 0 || check_y > SIZE ||
      check_y < 0)
            continue;
          if (check_x == a_i && check_y == a_j)
            continue;
          if (agents->get(check_x, check_y))
          {
            love_val += Agent::RelationshipMap[agent->id][agents->get(check_x, check_y)->id].love;
            ++agent_count;
          }
        }
      }
      int avg_love = (love_val/(agent_count + 1));
      // printf("avg love: %i\n", avg_love);
      kernel[i][j] = std::max(1, kernel[i][j] + agent->get_social_factor(avg_love));
      if (kernel[i][j] > max_l)
      {
        max_i = a_i - agent->vision_range + i;
        max_j = a_j - agent->vision_range + j;
        max_l = kernel[i][j];
      }
    }
  }

  // printf("max after love: %i\n", max_l);


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
    for (int j = 0; j <= 2*agent->vision_range; j++)
    {
      for (int i = 0; i <= 2*agent->vision_range; i++)
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
