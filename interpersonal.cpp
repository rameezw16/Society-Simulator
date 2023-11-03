#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <vector>

std::mt19937 mt(static_cast<unsigned>(std::time(0)));


class Entities
{
    public:
        std::string name;
        int health, wealth, happiness;
        int personalityTraits [5];

        Entities(std::string name)
        {
            this -> name = name;
            health = 30 + (mt() % 60);
            wealth = 30 + (mt() % 60);
            happiness = 20 + 0.2*(health*(mt()%4) + wealth*(mt()%4)); // max val is 20 + 0.2*(180 + 180) = 20 + 0.2*360 = 20 + 72 = 92
            printf("%s created with health: %i wealth: %i happiness: %i\n", this->name.c_str(), this->health, this->wealth, this->happiness);
        }
        
};

int main()
{
    for (int i = 0; i < 10; i++) std::cout << mt() << std::endl;
    Entities a = Entities("Joe");
    Entities b = Entities("Roe");
    Entities c = Entities("Boe");
    return 0;
}