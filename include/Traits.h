#pragma once

#include "Stats.h"

class Traits
{
    public:
        int openness;
        int conscientiousness;
        int extrovertedness;
        int agreeableness;
        int neuroticism;

        Traits(std::mt19937& mt, Stats* st) // randomise traits
        {
            this->openness = (mt() % 30) + 2*(20-st->age, 0) + st->wealth/4;
            this->conscientiousness = (mt() % 30) + 2*(20-st->age, 0) + st->wealth/4;
            this->extrovertedness = (mt() % 30) + 2*(20-st->age, 0) + st->wealth/4;
            this->agreeableness = (mt() % 30) + 2*(20-st->age, 0) + st->wealth/4;
            this->neuroticism = (mt() % 30) + 2*(20-st->age, 0) + st->wealth/4;
        }
};