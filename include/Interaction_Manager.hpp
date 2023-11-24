#pragma once
#include "Agent.hpp"
#include <random>
#include <ctime>
#include <set>

class Interaction_Manager
{
    public:
        static Interaction_Manager* getInstance();


        void interact(Agent* thisAgent, std::set<int>& occupied);
        void interact_all();

        void cycle_day();
        void cycle_year();

    private:
        // Interaction forms
        void interact_talk(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents);
        void interact_insult(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents);
        void interact_work(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents);
        void interact_hurt(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents);
        void interact_party(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents);
        void interact_reproduce(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents);
        void interact_idle(Agent* thisAgent);


        // Singleton
        static Interaction_Manager* instance;
        Interaction_Manager(const Interaction_Manager&) = delete;
        Interaction_Manager& operator=(const Interaction_Manager&) = delete;
        Interaction_Manager();

        int cur_day {0};
        int cur_year {0};

        int DAY_CYCLES = 3;
        int YEAR_CYCLES = 365;

        std::mt19937 mt;
};