#include <iostream>
#include <random>
#include <string>
#include <ctime>
#include <vector>
#include <map>
#include <fstream>

std::mt19937 mt(static_cast<unsigned>(std::time(0)));

class Entity
{
    private:
        int personalityTraits [5]; // Extroversion, Agreeableness, Openness, Conscientiousness, Neuroticism

    public:
        int id;
        static int count;
        std::string name;
        int health, wealth, happiness;
        std::map<int, std::vector<int>> relationShips; // Respect/Jealousy, Professional/Unprofessionalism, Love/Hate 

        Entity(std::string name, std::vector<Entity>& Entities)
        {
            this->id = count;
            count++;
            this->name = name;
            this->health = 30 + (mt() % 60);
            this->wealth = 30 + (mt() % 60);
            this->happiness = 20 + 0.2*(health*(mt()%4) + wealth*(mt()%4)); // max val is 20 + 0.2*(180 + 180) = 20 + 0.2*360 = 20 + 72 = 92
            this->personalityTraits[0] = mt()%50 + (this->health/10);

            std::ofstream entityFile;
            entityFile.open(name+".txt");
            entityFile << this->name << " created with id: " << this->id << " health: " << this->health << " wealth: " << this->wealth << " happiness: " << this->happiness << "\n";
            entityFile.close();

            for (Entity x : Entities)
            {
                this->initialise_Relation(&x);
                x.initialise_Relation(this);
            }
        }

        void initialise_Relation(Entity* other)
        {
            printf("Initialising %s -> %s\n", this->name.c_str(), other->name.c_str());
            int respect, professionalism, love;
            respect = (int) (other->wealth*(mt()%5 - 2) + other->happiness*(mt()%5 - 3)) / 5; // inner ranges from -200 - 300 -> 200 + 100
            professionalism = (int) (other->wealth*(mt()%5 - 2)) / 2;
            love = (int) ((other->wealth*(mt()%5 - 3) + other->happiness*(mt()%5 - 1)) + (mt()%30 - 14)) / 3; 
            relationShips[other->id] = {respect, professionalism, love};
            std::ofstream entityFile;
            entityFile.open(this->name+".txt", std::ios::app);
            entityFile << "Towards " << other->name << " has Respect: " << respect << " Professionalism: " << professionalism << " Love: " << love << std::endl;
            entityFile.close();
        }

        
};

int Entity::count = 0;
std::vector<Entity> Entities;


int main()
{
    // for (int i = 0; i < 10; i++) std::cout << mt() << std::endl;
    Entities.push_back(Entity("Joe", Entities));
    Entities.push_back(Entity("Roe", Entities));
    Entities.push_back(Entity("Boe", Entities));
    // Entities a = Entities("Joe");
    // Entities b = Entities("Roe");
    // Entities c = Entities("Boe");
    return 0;
}