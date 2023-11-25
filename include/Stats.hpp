#pragma once
#include <random>

enum GenderTypes {male, female}; // 0 -> male, 1 -> female

class Stats
{
    public:
        GenderTypes gender;
        int age {0};
        int health {0};
        int wealth {0};
        int happiness {0};

        Stats(std::mt19937& mt)
        {
            this->gender = (GenderTypes) (mt() % 2);
            this->age = mt() % 40;
            this->health = 30 + (mt() % 40) + std::max(50-age, 0)/2;
            this->wealth = 30 + (mt() % 70);
            this->happiness = (mt()%30) + this->health/3 + this->wealth/3; // happiness depends on health and wealth
        }

        Stats()
        {
            this->age = 0;
            this->health = 0;
            this->wealth = 0;
            this->happiness = 0;
        }

        Stats operator/(int div)
        {
            Stats new_stats;
            new_stats.age = this->age / div;
            new_stats.health = this->health / div;
            new_stats.wealth = this->wealth / div;
            new_stats.happiness = this->happiness / div;
            return new_stats;
        }
};