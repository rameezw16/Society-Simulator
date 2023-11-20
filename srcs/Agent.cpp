#include "../include/Agent.hpp"

// #include <string>
#include <random>
#include <ctime>
#include <fstream>

Agent::Agent(std::string name, std::mt19937& mt)
{
    this->id = count++;
    this->name = name;
    this->aStats = new Stats(mt); // constructor has initialisation formulas
    this->aTraits = new Traits(mt, this->aStats); // constructor has initialisation formulas

    // Add details to file
    std::ofstream agentFile;
    agentFile.open("../logs/"+this->name+".txt");
    agentFile << this->name << " created with id: " << this->id << ", age: " << this->aStats->age << ", health: " << this->aStats->health << ", wealth: " << this->aStats->wealth << ", happiness: " << this->aStats->happiness << "\n";
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

Agent::~Agent()
{
    // display_agent_list();
    // display_relation_map();
    delete this->aStats;
    delete this->aTraits;
    RelationshipMap.erase(this->id);
    AgentList.erase(this->id);
    for (std::pair<int, Agent*> i : AgentList)  RelationshipMap[i.second->id].erase(this->id);
}