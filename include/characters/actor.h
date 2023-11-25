#pragma once
#include "../entity.h"
#include "../Relationship.hpp"
#include "../Stats.hpp"
#include "../Traits.hpp"
#include "../size.h"
#include <random>
#include <vector>
#include <map>
#include <string>
#include <fstream>

class Agent : public Entity 
{
    public:
	  Agent(std::mt19937 &mt, const int spritesheet_pos_x = 0,
			const int spritesheet_pos_y = 0, std::string name = "", int posX = -1,
			int posY = -1);
      virtual ~Agent();

  void interact_randomly() override;

      static int count;
      static std::map<int, Agent *> AgentList;
      static std::map<int, std::map<int, Relationship>> RelationshipMap;
      static std::vector<std::string> fname_list;
      static std::vector<std::string> lname_list;

      int id;
      std::string name = "";
      int age;
      Stats *aStats;
      int posX = -1, posY = -1;

      void initialise_relations();

      void move_agent(int posX, int posY);

      void new_day(int year, int day);

      void grow();

      void display_agent_list();
      void display_relation_map();

      void is_dead();

    private:
        Traits* aTraits;
        Relationship relationSum {0, 0};

        static int GRID_WIDTH ;
        static int GRID_HEIGHT ;

    friend class Interaction_Manager;
};



