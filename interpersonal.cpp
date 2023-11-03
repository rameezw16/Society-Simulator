#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <vector>
#include <fstream>

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
            std::ofstream entityFile;
            entityFile.open(name+".txt");
            entityFile << this->name << " created with health: " << this->health << " wealth: " << this->wealth << " happiness: " << this->happiness << "\n";
            entityFile.close();
        }
        
};

int main()
{
    // for (int i = 0; i < 10; i++) std::cout << mt() << std::endl;
    Entities a = Entities("Joe");
    Entities b = Entities("Roe");
    Entities c = Entities("Boe");
    return 0;
}