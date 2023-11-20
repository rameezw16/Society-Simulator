#pragma once
#include <random>

class Stats
{
    public:
        int age;
        int health;
        int wealth;
        int happiness;

        Stats(std::mt19937& mt)
        {
            this->age = mt() % 40;
            this->health = 30 + (mt() % 40) + std::max(50-age, 0)/2;
            this->wealth = 30 + (mt() % 70);
            this->happiness = (mt()%30) + this->health/3 + this->wealth/3; // happiness depends on health and wealth
        }
};