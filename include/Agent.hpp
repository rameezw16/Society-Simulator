#pragma once
#include "Relationship.hpp"
#include "Stats.hpp"
#include "Traits.hpp"

#include <random>
#include <vector>
#include <map>
#include <string>

class Agent
{
    public:
        static int count;
        static std::map<int, Agent*> AgentList;
        static std::map<int, std::map<int, Relationship>> RelationshipMap;
        static std::vector<std::string> fname_list;
        static std::vector<std::string> lname_list;

        int id;
        std::string name;
        int age;
        Stats* aStats;
        int posX, posY;

        Agent(std::mt19937& mt, std::string name = "", int posX = -1, int posY = -1);
        
        void initialise_relations();

        void move_agent(int posX, int posY);

        void new_day(int year, int day);

        void display_agent_list();
        void display_relation_map();

        ~Agent();

    private:
        Traits* aTraits;
        Relationship relationSum {0, 0};

        int GRID_WIDTH {60};
        int GRID_HEIGHT {60};
};