#include "characters/actor.h"
#include <string>

class Interaction_Manager_2
{
    private:
         
    public:
        std::string pick_interaction(Agent* thisAgent, Agent* otherAgent); // pick action to do
        void interact(Agent* thisAgent, std::string action); // perform the action
};