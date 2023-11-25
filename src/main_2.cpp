#include "../include/Agent.hpp"
#include "../include/Interaction_Manager.hpp"

#include <ctime>
#include<iostream>
#include <filesystem>
#include <fstream>

std::mt19937 mt(static_cast<int>(std::time(0)));

Stats get_avg_stats()
{
    Stats avg_stats;
    for (std::pair<int, Agent*> agent : Agent::AgentList)
    {
        avg_stats.age += agent.second->aStats->age;
        avg_stats.health += agent.second->aStats->health;
        avg_stats.wealth += agent.second->aStats->wealth;
        avg_stats.happiness += agent.second->aStats->happiness;
    }

    avg_stats = avg_stats / ((int) Agent::AgentList.size());
    return avg_stats;
}

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

void run(int starting_population, int num_years, std::mt19937 mt)
{
    for (int i = 0; i < starting_population; i++)
        new Agent(mt);


    std::string summary_file = "_Summary";
    std::ofstream sum_file;
    sum_file.open("../logs/"+summary_file+".txt");
    sum_file << "Starting with: " << Agent::AgentList.size() << " Agents\n";

    Stats avg_stats;
    avg_stats = get_avg_stats();

    sum_file << "Starting Avg Health: " << avg_stats.health << std::endl;
    sum_file << "Starting Avg Wealth: " << avg_stats.wealth << std::endl;
    sum_file << "Starting Avg Happiness: " << avg_stats.happiness << std::endl;
    sum_file << "Starting Avg Age: " << avg_stats.age << std::endl;
    sum_file << std::endl;
    

    
    // sum_file << "Starting Avg Love: " << get_avg_health() << std::endl;
    // sum_file << "Starting Avg Respect: " << get_avg_health() << std::endl << std::endl;

    sum_file.close();

    Interaction_Manager* Int_Manager = Interaction_Manager::getInstance();
    for (int i = 0; i < num_years; i++)
        Int_Manager->cycle_year(); // 1 year = 365 days = 365 * 3 interaction cycles

    sum_file.open("../logs/"+summary_file+".txt", std::ios::app);
    
    avg_stats = get_avg_stats();
    sum_file << "Ending with: " << Agent::AgentList.size() << " Agents\n";
    sum_file << "Ending Avg Health: " << avg_stats.health << std::endl;
    sum_file << "Ending Avg Wealth: " << avg_stats.wealth << std::endl;
    sum_file << "Ending Avg Happiness: " << avg_stats.happiness << std::endl;
    sum_file << "Ending Avg Age: " << avg_stats.age << std::endl;
    sum_file << std::endl;

    // sum_file << "Ending Avg Love: " << get_avg_health() << std::endl;
    // sum_file << "Ending Avg Respect: " << get_avg_health() << std::endl << std::endl;


    sum_file << "Total Births: " << Agent::count - starting_population << std::endl;
    sum_file << "Total Deaths: " << Agent::count - Agent::AgentList.size() << std::endl;

    Int_Manager->summary_output();

    // clean up
    std::vector<Agent*> agents;
    for (std::pair<int, Agent*> agent : Agent::AgentList)
        agents.push_back(agent.second);

    for (Agent* agent : agents)
        delete agent;
}

int main()
{
    clearDirectory("../logs");

    run(30, 2, mt);
}

