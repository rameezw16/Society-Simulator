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

        int id;
        std::string name;
        int age;
        Stats* aStats;

        Agent(std::string name, std::mt19937& mt);
        
        void initialise_relations();

        void display_agent_list();
        void display_relation_map();

        ~Agent();

    private:
        Traits* aTraits;
        Relationship relationSum {0, 0};
};