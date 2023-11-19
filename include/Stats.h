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
            this->health = 30 + (mt() % 60) - 0.3*this->age;
            this->wealth = 30 + (mt() % 60);
            this->happiness = (mt()%20) + 0.15*this->health*(mt() % 4) + 0.1*this->wealth*(mt() % 4); // happiness depends on health and wealth
        }
};