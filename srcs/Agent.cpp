#include "../include/Agent.hpp"

// #include <string>
#include <random>
#include <ctime>
#include <fstream>

Agent::Agent(std::mt19937& mt, std::string name, int posX, int posY)
{
    this->id = count++;
    if (name.length())
        this->name = name;
    else
        this->name = fname_list[mt()%fname_list.size()] + " " + lname_list[mt()%lname_list.size()];

    if (posX != -1)
        this->posX = posX;
    else
        this->posX = mt() % GRID_WIDTH;

    if (posY != -1)
        this->posY = posY;
    else
        this->posY = mt() % GRID_HEIGHT;

    this->aStats = new Stats(mt); // constructor has initialisation formulas
    this->aTraits = new Traits(mt, this->aStats); // constructor has initialisation formulas

    // Add details to file
    std::ofstream agentFile;
    agentFile.open("../logs/"+this->name+".txt");
    agentFile << this->name << " created at (" << this->posX << ", " << this->posY << ") with id: " << this->id << ", gender: " << ((this->aStats->gender) ? "male" : "female") << ", age: " << this->aStats->age << ", health: " << this->aStats->health << ", wealth: " << this->aStats->wealth << ", happiness: " << this->aStats->happiness << "\n";
    agentFile << "and personality traits:  Openness: " << this->aTraits->openness << ", Conscientiousness: " << this->aTraits->conscientiousness << ", Extrovertedness: " << this->aTraits->extrovertedness << ", Agreeableness: " << this->aTraits->agreeableness << ", Neuroticism: " << this->aTraits->neuroticism << std::endl;
    agentFile.close();
    
    // add relations
    this->initialise_relations();

    // store Agent in list
    AgentList[this->id] = this;
}

void Agent::initialise_relations()
{
    std::map<int, Relationship> this_relations;
    for (std::pair<int, Agent*> i : AgentList)
    {
        Agent* other = i.second;

        // Relation of this with other - based off stats and traits
        this_relations[other->id] = Relationship(this->aStats, this->aTraits, other->aStats);
        Relationship cur = this_relations[other->id];
        this->relationSum = this->relationSum + cur;
        
        // add to file
        printf("adding relation of %s with %s\n", this->name.c_str(), other->name.c_str());
        std::ofstream agentFile;
        agentFile.open("../logs/"+this->name+".txt", std::ios::app);
        agentFile << "Towards " << other->name << " has Love: " << cur.love << ", Respect: " << cur.respect << std::endl;
        agentFile.close();

        // Relation of other with this - based off stats and traits
        RelationshipMap[other->id][this->id] = Relationship(other->aStats, other->aTraits, this->aStats);
        cur = RelationshipMap[other->id][this->id];
        other->relationSum = other->relationSum + cur;

        // add to file
        printf("adding relation of %s with %s\n", other->name.c_str(), this->name.c_str());
        agentFile.open("../logs/"+other->name+".txt", std::ios::app);
        agentFile << "Towards " << this->name << " has Love: " << cur.love << ", Respect: " << cur.respect << std::endl;
        agentFile.close();
        
    }
    RelationshipMap[this->id] = this_relations;
}

void Agent::move_agent(int posX, int posY)
{
    this->posX = posX;
    this->posY = posY;
    std::ofstream agentFile;
    agentFile.open("../logs/"+this->name+".txt", std::ios::app);
    agentFile << "Moved to pos: (" << this->posX << ", " << this->posY << ")" << std::endl;
    agentFile.close();
}

void Agent::new_day(int year, int day)
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+this->name+".txt", std::ios::app);
    agentFile << "Year: " << year << ", Day: " << day << std::endl;
    agentFile.close();
}

void Agent::display_agent_list()
{
    for (std::pair<int, Agent*> i : AgentList)
    {
        printf("%i, ", i.first);
    }
    printf("\n");
}

void Agent::display_relation_map()
{
    for (std::pair<int, std::map<int, Relationship>> i : RelationshipMap)
    {
        for (std::pair<int, Relationship> j : i.second)
        {
            printf("%i -> %i\n", i.first, j.first);
        }
    }
    printf("\n");
}

void Agent::is_dead()
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+this->name+".txt", std::ios::app);
    if (this->aStats->health <= 0)
    {
        agentFile << "Died due to poor health" << std::endl;
        agentFile.close();
        delete this;
    }
    else if (this->aStats->wealth <= 0)
    {
        agentFile << "Died due to poverty" << std::endl;
        agentFile.close();
        delete this;
    }
    else if (this->aStats->happiness <= 0)
    {
        agentFile << "Died due to depression" << std::endl;
        agentFile.close();
        delete this;
    }
    if (agentFile.is_open()) agentFile.close();
}

Agent::~Agent()
{
    // display_agent_list();
    // display_relation_map();
    delete this->aStats;
    delete this->aTraits;
    RelationshipMap.erase(this->id);
    AgentList.erase(this->id);
    for (std::pair<int, Agent*> i : AgentList)  
    {   
        i.second->relationSum = i.second->relationSum - RelationshipMap[i.second->id][this->id];
        i.second->aStats->happiness += (40 - RelationshipMap[i.second->id][this->id].love)/3; // sad to see loved one die - happy to see hated one die
        i.second->aStats->happiness = std::max(i.second->aStats->happiness, 0);
        RelationshipMap[i.second->id].erase(this->id);
    }
}

int Agent::count = 0;
std::map<int, Agent*> Agent::AgentList;
std::map<int, std::map<int, Relationship>> Agent::RelationshipMap;
std::vector<std::string> Agent::fname_list = {"John", "Anna", "Mark", "Emma", "Paul", "Laura", "Alex", "Grace"};
std::vector<std::string> Agent::lname_list = {"Smith", "Johnson", "Brown", "Taylor", "Jones", "Miller", "Davis", "Garcia"};