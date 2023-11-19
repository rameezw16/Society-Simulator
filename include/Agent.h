#pragma once
#include "Relationship.h"
#include "Stats.h"
#include "Traits.h"

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

    private:
        Traits* aTraits;
        Relationship* relationSum;
};