#pragma once
#include "Stats.hpp"
#include "Traits.hpp"

#include <random>

class Relationship
{
    public:
        int love;
        int respect;
        // int professionalism; (not required)

        Relationship(int l = 0, int r = 0);

        Relationship(Stats* thisStats, Traits* thisTraits, Stats* otherStats);

        Relationship operator +(Relationship& other);
};