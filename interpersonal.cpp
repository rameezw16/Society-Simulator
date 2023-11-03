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
    // private:

    public:
        int personalityTraits [5]; // Extroversion, Agreeableness, Openness, Conscientiousness, Neuroticism
        int id;
        static int count;
        std::string name;
        int health, wealth, happiness;
        int totalRespect, totalProfessionalism, totalLove;
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
            this->totalProfessionalism += professionalism;
            this->totalRespect += respect;
            this->totalLove += love;
            relationShips[other->id] = {respect, professionalism, love};
            std::ofstream entityFile;
            entityFile.open(this->name+".txt", std::ios::app);
            entityFile << "Towards " << other->name << " has Respect: " << respect << " Professionalism: " << professionalism << " Love: " << love << std::endl;
            entityFile.close();
        }
};

std::vector<Entity> Entities;

class Interaction
{
    public:
        virtual void interact(Entity& p1) = 0;
};

class SocialInteraction : public Interaction
{
    public:
        void interact(Entity& p1)
        {
            int choice = mt()%1;
            switch (choice)
            {
                case 0:
                    Talk(p1);
                    break;

                case 1:
                    Hurt(p1);
                    break;

                case 2:
                    Help(p1);
                    break;

            }
        }
        void Talk(Entity& p1)
        {
            int c = mt() % (p1.totalLove);
            int curLove = 0;
            int other_id = 0;
            for (auto x : p1.relationShips)
            {
                curLove += x.second[2];
                other_id = x.first;
                if (curLove > c) break;
            }
            Entity& p2 = Entities[other_id];

            p1.happiness += (int) ((p1.personalityTraits[0] - 30) * mt() % 4) / 3;
            int x = (mt() % 7 - 2) ;
            p1.relationShips[other_id][2] += x;
            p1.totalLove += x;

            std::ofstream p1File;
            p1File.open(p1.name+".txt", std::ios::app);
            p1File << p1.name << " talked to " << p2.name << std::endl;
            p1File << p1.name << " has happiness: " << p1.happiness << " and loves " << p2.name << " " << x << " units more"   << "\n";
            
            p1File.close();

            p2.happiness += (int) ((p2.personalityTraits[0] - 30) * mt() % 4) / 3;
            int y = (mt() % 7 - 2) ;
            p2.relationShips[p1.id][2] += y;
            p2.totalLove += x;


            std::ofstream p2File;
            p1File.open(p2.name+".txt", std::ios::app);
            p1File << p1.name << " talked to " << p2.name << std::endl;
            p1File << p2.name << " has happiness: " << p2.happiness << " and loves " << p1.name << " " << y << " units more"   << "\n";
            

        }
        void Hurt(Entity& p1)
        {
            return;
        }
        void Help(Entity& p1)
        {
            return;
        }
};

int Entity::count = 0;


int main()
{
    // for (int i = 0; i < 10; i++) std::cout << mt() << std::endl;
    Entities.push_back(Entity("Joe", Entities));
    Entities.push_back(Entity("Roe", Entities));
    Entities.push_back(Entity("Boe", Entities));

    Interaction* act = new SocialInteraction();

    for (int i = 0; i < 10; i++)
    {
        for (Entity& x : Entities)
        {
            act->interact(x);
        }
    }
    // Entities a = Entities("Joe");
    // Entities b = Entities("Roe");
    // Entities c = Entities("Boe");
    return 0;
}