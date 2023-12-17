#include "characters/agent.h"
#include <random>
#include <string>

class Interaction_Manager_2 {
private:
  void interact_talk(Agent *thisAgent, Agent *otherAgent);
  void interact_hurt(Agent *thisAgent, Agent *otherAgent);
  std::mt19937 mt;

public:
  Interaction_Manager_2(unsigned seed);
  std::string pick_interaction(Agent *thisAgent,
                               Agent *otherAgent); // pick action to do
  void interact(Agent *thisAgent, Agent *otherAgent,
                std::string action); // perform the action
};
