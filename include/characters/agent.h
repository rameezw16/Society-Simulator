#pragma once
#include "../Relationship.hpp"
#include "../Stats.hpp"
#include "../Traits.hpp"
#include "../entity.h"
#include "../size.h"
#include <fstream>
#include <map>
#include <random>
#include <string>
#include <vector>

class Agent : public Entity {
public:
  Agent(std::mt19937 &mt, const int spritesheet_pos_x = 0,
        const int spritesheet_pos_y = 0, std::string name = "", int posX = 30,
        int posY = 30);

  virtual ~Agent();

  bool get_walkable() const;
  std::string get_type() const;

  static int count;
  static std::map<int, Agent *> AgentList;
  static std::map<int, std::map<int, Relationship>> RelationshipMap;
  static std::vector<std::string> fname_list;
  static std::vector<std::string> lname_list;

  int id;
  std::string name = "";
  int age;
  Stats *aStats;
  int vision_range = 2;
  int reproduction_factor = 0;

  void initialise_relations();

  void move_agent(int posX, int posY);

  void new_day(int year, int day);

  void grow();

  void display_agent_list();
  void display_relation_map();

  // void is_dead();
  bool is_dead();

  int posX = 30, posY = 30;

  bool walkable = false;

  // Hamad's changes start here

  void step() override;
  void consume() override;
  void decay() override;
  void grow_back() override;

  bool attempt_reproduce();

  Entity *goal_entity{nullptr};
  int goal_x, goal_y{};
  std::string action{};

  int amount_of_food;
  int metabolism; // each step reduce by this amount
  int vision;     // size of vision

private:
  Traits *aTraits;
  Relationship relationSum{0, 0};

  static int GRID_WIDTH;
  static int GRID_HEIGHT;

  friend class Interaction_Manager;
};
