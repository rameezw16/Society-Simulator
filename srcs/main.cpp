#include "../include/Agent.hpp"
#include "../include/Interaction_Manager.hpp"

#include <ctime>
#include<iostream>
#include <filesystem>

std::mt19937 mt(static_cast<int>(std::time(0)));


void clearDirectory(const std::string& path) {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            // Remove the entry
            std::filesystem::remove_all(entry);
        }
        std::cout << "Directory cleared successfully." << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error clearing directory: " << e.what() << std::endl;
    }
}

// to do: tune variables. reduce reproduction attempts
int main()
{
    clearDirectory("../logs");

    for (int i = 0; i < 30; i++)
    {
        new Agent(mt);
    }

    Interaction_Manager* Int_Manager = Interaction_Manager::getInstance();
    for (int i = 0; i < 50; i++)
        Int_Manager->cycle_year(); // 1 year = 365 days = 365 * 3 interaction cycles

    std::vector<Agent*> agents;
    for (std::pair<int, Agent*> agent : Agent::AgentList)
        agents.push_back(agent.second);

    for (Agent* agent : agents)
        delete agent;
    
}