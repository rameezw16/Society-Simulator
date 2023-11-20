#include "../include/Agent.hpp"
#include "../include/Stats.hpp"

// #include <string>
#include <random>
#include <ctime>
#include <fstream>


Agent::Agent(std::string name, std::mt19937& mt)
{
    this->id = count++;
    this->name = name;
    this->aStats = new Stats(mt);
    this->aTraits = new Traits(mt, this->aStats);
    // this->initialise_relation();

    // Add details to file
    std::ofstream agentFile;
    agentFile.open("../logs/"+this->name+".txt");
    agentFile << this->name << " created with id: " << this->id << ", age: " << this->aStats->age << ", health: " << this->aStats->health << ", wealth: " << this->aStats->wealth << ", happiness: " << this->aStats->happiness << "\n";
    agentFile << "and personality traits:  Openness: " << this->aTraits->openness << ", Conscientiousness: " << this->aTraits->conscientiousness << ", Extrovertedness: " << this->aTraits->extrovertedness << ", Agreeableness: " << this->aTraits->agreeableness << ", Neuroticism: " << this->aTraits->neuroticism << std::endl;
    agentFile.close();
}

Agent::~Agent()
{
    delete this->aStats;
    delete this->aTraits;
}