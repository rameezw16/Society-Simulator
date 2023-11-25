#pragma once

#include "Stats.hpp"

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
            this->openness = (mt() % 30) + std::max(30-st->age, 0) + st->wealth/3; // less open as you age, more open as you get wealthier
            this->conscientiousness = (mt() % 20) + std::min(st->age, 30) + st->health/4 + st->wealth/4; // more conscientious as you age and if you are healthy or wealthy
            this->extrovertedness = (mt() % 40) + std::max(40-st->age, 0)/2 + std::max(60-st->wealth, 0)/3 + st->happiness/5; // less extroverted as you age or get wealthy. More extroverted if you are happy
            this->agreeableness = (mt() % 20) + std::max(40-st->age, 0)/2 + std::max(60-st->wealth, 0)/2 + st->happiness/5 + 10*st->gender; // less agreeable as you age or get wealthier. More agreeable if happy or female.
            this->neuroticism = (mt() % 30) + std::max(60-st->health, 0)/2 + std::max(60-st->happiness, 0)/2 + 10*st->gender; // less neurotic as you are healthier and happier. More neurotic if female.
        }
};