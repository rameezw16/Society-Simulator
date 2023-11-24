#pragma once
#include "Agent.hpp"

class Interaction_Manager
{
    public:
        static Interaction_Manager* getInstance();


        int interact(Agent* thisAgent);
        void interact_all();

        void cycle_day();
        void cycle_year();

    private:
        static Interaction_Manager* instance;
        Interaction_Manager();

        int cur_day {0};
        int cur_year {0};

        int DAY_CYCLES = 3;
        int YEAR_CYCLES = 365;
};