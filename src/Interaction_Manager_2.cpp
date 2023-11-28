#include "../include/Interaction_Manager_2.hpp"
#include <iostream>

// Constructor
Interaction_Manager_2::Interaction_Manager_2(unsigned seed)
{
    this->mt = std::mt19937(seed);
}

// Interaction Decider
std::string Interaction_Manager_2::pick_interaction(Agent* thisAgent, Agent* otherAgent)
{
    if (thisAgent->aStats->happiness > 50)
        return "talk";
    else
        return "hurt";
}

// Interaction Redirecter
void Interaction_Manager_2::interact(Agent* thisAgent, Agent* otherAgent, std::string action)
{
    if (action == "talk")
        interact_talk(thisAgent, otherAgent);
    else if (action == "hurt")
        interact_hurt(thisAgent, otherAgent);
}

void Interaction_Manager_2::interact_talk(Agent* thisAgent, Agent* otherAgent)
{
    std::cout << "talk\n";

    int modifier = 1 + mt() % 3; 

    thisAgent->aStats->happiness = std::min(thisAgent->aStats->happiness + modifier, 100);
    otherAgent->aStats->happiness = std::min(otherAgent->aStats->happiness + modifier, 100);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].love = std::min(Agent::RelationshipMap[thisAgent->id][otherAgent->id].love + modifier, 100);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].love = std::min(Agent::RelationshipMap[otherAgent->id][thisAgent->id].love + modifier, 100);

    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Talked to " << otherAgent->name << std::endl;
    agentFile.close();

    agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
    agentFile << "Talked to " << thisAgent->name << std::endl;
    agentFile.close();

    std::cout << "talk completed\n";
}

void Interaction_Manager_2::interact_hurt(Agent* thisAgent, Agent* otherAgent)
{
    std::cout << "hurt\n";

    int modifier = 1 + mt() % 3; 

    thisAgent->aStats->happiness = std::min(thisAgent->aStats->happiness + 3*modifier, 100);
    otherAgent->aStats->happiness = std::max(otherAgent->aStats->happiness - 3*modifier, 0);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].love = std::max(Agent::RelationshipMap[thisAgent->id][otherAgent->id].love - modifier, 0);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].love = std::max(Agent::RelationshipMap[otherAgent->id][thisAgent->id].love - modifier, 0);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect = std::max(Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect - modifier, 0);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect = std::max(Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect - modifier, 0);

    otherAgent->aStats->health = std::max(otherAgent->aStats->health - modifier, 0);

    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Hurt " << otherAgent->name << std::endl;
    agentFile.close();

    agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
    agentFile << "Hurt by " << thisAgent->name << std::endl;
    agentFile.close();

    std::cout << "hurt completed\n";
}