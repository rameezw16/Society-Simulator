#pragma once
#include "characters/agent.h"
#include <ctime>
#include <random>
#include <set>

// This class manages interactions between randomly generated agents. It is a
// singleton.

class Interaction_Manager {
public:
  static Interaction_Manager *getInstance();

  void interact(Agent *thisAgent, std::set<int> &occupied);
  void interact_all();

  void cycle_day();
  void cycle_year();

  void summary_output();

private:
  // Interaction forms
  void
  interact_talk(Agent *thisAgent, std::set<int> &occupied,
                std::vector<std::pair<int, int>> &nearby_unoccupied_agents);
  void
  interact_insult(Agent *thisAgent, std::set<int> &occupied,
                  std::vector<std::pair<int, int>> &nearby_unoccupied_agents);
  void
  interact_work(Agent *thisAgent, std::set<int> &occupied,
                std::vector<std::pair<int, int>> &nearby_unoccupied_agents);
  void
  interact_hurt(Agent *thisAgent, std::set<int> &occupied,
                std::vector<std::pair<int, int>> &nearby_unoccupied_agents);
  void
  interact_party(Agent *thisAgent, std::set<int> &occupied,
                 std::vector<std::pair<int, int>> &nearby_unoccupied_agents);
  void interact_reproduce(
      Agent *thisAgent, std::set<int> &occupied,
      std::vector<std::pair<int, int>> &nearby_unoccupied_agents);
  void interact_idle(Agent *thisAgent);

  // Singleton
  static Interaction_Manager *instance;
  Interaction_Manager(const Interaction_Manager &) = delete;
  Interaction_Manager &operator=(const Interaction_Manager &) = delete;
  Interaction_Manager();

  int cur_day{0};
  int cur_year{0};
  std::string summary_file;

  int total_talk{0};
  int total_insult{0};
  int total_work{0};
  int total_hurt{0};
  int total_party{0};
  int total_reproduce_attempts{0};
  int total_idles{0};

  int DAY_CYCLES = 3;
  int YEAR_CYCLES = 365;

  std::mt19937 mt;
};
