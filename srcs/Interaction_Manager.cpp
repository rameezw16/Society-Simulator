#include "../include/Interaction_Manager.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <set>

Interaction_Manager* Interaction_Manager::getInstance()
{
    if (!instance) instance = new Interaction_Manager();
    return instance;
}

void Interaction_Manager::interact(Agent* thisAgent, std::set<int>& occupied)
{
    // std::cout << thisAgent->id << std::endl;

    std::vector<int> choice_probability 
    {
        thisAgent->aTraits->extrovertedness/5, // talk - max 20% - increases with extroversion
        thisAgent->aTraits->neuroticism/10 + thisAgent->aTraits->openness/10, // insult - max 20% - increases with neuroticism and openness
        (thisAgent->aTraits->conscientiousness + std::max(50 - thisAgent->aStats->wealth, 0))/10, // work - max 15% - increases with conscientiousness and lack of money
        thisAgent->aTraits->neuroticism/10, // hurt - max 10% - increases with neuroticism
        thisAgent->aTraits->extrovertedness/10 + std::max(40 - thisAgent->aStats->age, 0)/4, // party - max 20% - increases with extroversion, reduces with age
        thisAgent->aStats->health/20 + thisAgent->aStats->happiness/20 + thisAgent->aStats->wealth/20 // reproduce - max 15% - increases with wealth, health and happiness
    };

    std::vector<int> choice_probability_prefix = {choice_probability[0]};
    for (int i = 1; i < choice_probability.size(); i++)
        choice_probability_prefix[i] = choice_probability_prefix[i-1] + choice_probability[i];

    int choice = (this->mt() % 100);
    // talk, insult, work with, hurt, party, reproduce
    if (choice < choice_probability_prefix[0])
        this->interact_talk(thisAgent, occupied);
    else if (choice < choice_probability_prefix[1])
        this->interact_insult(thisAgent, occupied);
    else if (choice < choice_probability_prefix[2])
        this->interact_work(thisAgent, occupied);
    else if (choice < choice_probability_prefix[3])
        this->interact_hurt(thisAgent, occupied);
    else if (choice < choice_probability_prefix[4])
        this->interact_party(thisAgent, occupied);
    else if (choice < choice_probability_prefix[5])
        this->interact_reproduce(thisAgent, occupied);
    // else
        // std::cout << thisAgent->id << " idled" << std::endl;
    return;
}

void Interaction_Manager::interact_all()
{
    std::vector<int> agents = {};
    for (std::pair<int, Agent*> agent : Agent::AgentList)
        agents.push_back(agent.first);

    std::shuffle(agents.begin(), agents.end(), mt);

    std::set<int> occupied {};

    // std::cout << "Interaction cycle:" << std::endl;
    for (int i : agents)
    {
        if (!occupied.count(i))
        {
            occupied.insert(i);
            this->interact(Agent::AgentList[i], occupied);
            // occupied.insert(this->interact(Agent::AgentList[i]));
        }
    }

    for (int i : agents)
    {
        Agent::AgentList[i]->is_dead();
    }
    return;
}

void Interaction_Manager::cycle_day()
{
    for (std::pair<int, Agent*> agent : Agent::AgentList)
    {
        agent.second->new_day(this->cur_year, this->cur_day);
    }

    for (int i = 0; i < DAY_CYCLES; i++)
        interact_all();

    this->cur_day++; // next day
    if (cur_day > 365)
        cur_day = 1, cur_year++;
}

void Interaction_Manager::cycle_year()
{
    for (int i = 0; i < 365; i++)
        this->cycle_day();
}

Interaction_Manager::Interaction_Manager()
{
    instance = this;
    cur_day = 1;
    cur_year = 1;
    this->mt = std::mt19937(static_cast<int>(std::time(0)));;
}

Interaction_Manager* Interaction_Manager::instance {nullptr};

void Interaction_Manager::interact_talk(Agent* thisAgent, std::set<int>& occupied)
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Tried to talk" << std::endl;
    thisAgent->aStats->happiness -= 20;
    agentFile.close();
}

void Interaction_Manager::interact_insult(Agent* thisAgent, std::set<int>& occupied)
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Tried to insult" << std::endl;
    thisAgent->aStats->health -= 20;
    agentFile.close();
}
void Interaction_Manager::interact_work(Agent* thisAgent, std::set<int>& occupied)
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Tried to work" << std::endl;
    thisAgent->aStats->wealth -= 20;
    agentFile.close();
}
void Interaction_Manager::interact_hurt(Agent* thisAgent, std::set<int>& occupied)
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Tried to hurt" << std::endl;
    agentFile.close();
}
void Interaction_Manager::interact_party(Agent* thisAgent, std::set<int>& occupied)
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Tried to party" << std::endl;
    agentFile.close();
}
void Interaction_Manager::interact_reproduce(Agent* thisAgent, std::set<int>& occupied)
{
    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Tried to reproduce" << std::endl;
    agentFile.close();
}