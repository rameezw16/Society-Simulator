#include "../include/Agent.hpp"
#include <ctime>

std::mt19937 mt(static_cast<int>(std::time(0)));

int Agent::count = 0;
std::map<int, Agent*> Agent::AgentList;
std::map<int, std::map<int, Relationship>> Agent::RelationshipMap;



int main()
{
    Agent* tmp1 = new Agent("bob", mt);
    Agent* tmp2 = new Agent("rob", mt);
    Agent* tmp3 = new Agent("job", mt);

    for (std::pair<int, Agent*> i : Agent::AgentList)
    {
        printf("%i : %s\n", i.first, i.second->name.c_str());
    }
    delete tmp1;
    delete tmp2;
    delete tmp3;
}