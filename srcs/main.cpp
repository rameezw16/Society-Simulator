#include "../include/Agent.hpp"
#include <ctime>

std::mt19937 mt(static_cast<int>(std::time(0)));


int main()
{
    Agent* tmp1 = new Agent(mt, "Rob", 33, 24);
    Agent* tmp2 = new Agent(mt, "Bob");
    tmp2->move_agent(7, 15);
    Agent* tmp3 = new Agent(mt, "Job");

    // for (std::pair<int, Agent*> i : Agent::AgentList)
    // {
    //     printf("%i : %s\n", i.first, i.second->name.c_str());
    // }
    delete tmp1;
    delete tmp2;
    delete tmp3;
}