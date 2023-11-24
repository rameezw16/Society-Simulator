#include "../include/Interaction_Manager.hpp"

Interaction_Manager* Interaction_Manager::getInstance()
{
    if (!instance) instance = new Interaction_Manager();
    return instance;
}

// int Interaction_Manager::interact(Agent* thisAgent)
// {
//     // thisAgent->aTraits->agreeableness = 5;
// }

void Interaction_Manager::interact_all()
{
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

    this->cur_day++;
}

Interaction_Manager::Interaction_Manager()
{
    instance = this;
    cur_day = 1;
    cur_year = 1;
}

Interaction_Manager* Interaction_Manager::instance {nullptr};