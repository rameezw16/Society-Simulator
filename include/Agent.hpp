#pragma once
#include "Relationship.hpp"
#include "Stats.hpp"
#include "Traits.hpp"

#include <random>
#include <vector>
#include <string>

class Agent
{
    public:
        static int count;
        static std::vector<Relationship> RelationshipMatrix;

        int id;
        std::string name;
        int age;
        Stats* aStats;

        Agent(std::string name, std::mt19937& mt);
        ~Agent();

    private:
        Traits* aTraits;
        Relationship* relationSum;
};