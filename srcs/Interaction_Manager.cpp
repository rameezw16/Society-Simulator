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
    std::vector<std::pair<int, int>> nearby_unoccupied_agents;// manhattan distance
    for (std::pair<int, Agent*> agent : Agent::AgentList)
    {
        if (!occupied.count(agent.first))
        {
            // printf("This Agent: %i, Other: %i\n", thisAgent->id, agent.first);
            nearby_unoccupied_agents.push_back({1 + abs(thisAgent->posX - agent.second->posX) +  abs(thisAgent->posY - agent.second->posY), agent.first}); // 1 added to keep distance non-zero
        }
    }
    
    if (!nearby_unoccupied_agents.size()) // no agents to interact with
    {
        this->interact_idle(thisAgent);
        return;
    }

    sort(nearby_unoccupied_agents.begin(), nearby_unoccupied_agents.end());

    std::vector<int> choice_probability 
    {
        thisAgent->aTraits->extrovertedness/5, // talk - max 20% - increases with extroversion
        thisAgent->aTraits->neuroticism/10 + thisAgent->aTraits->openness/10, // insult - max 20% - increases with neuroticism and openness
        (thisAgent->aTraits->conscientiousness + std::max(50 - thisAgent->aStats->wealth, 0))/10, // work - max 15% - increases with conscientiousness and lack of money
        thisAgent->aTraits->neuroticism/10 + (100 - thisAgent->relationSum.love/((int) Agent::AgentList.size()))/20, // hurt - max 15% - increases with neuroticism
        thisAgent->aTraits->extrovertedness/10 + std::max(40 - thisAgent->aStats->age, 0)/8, // party - max 15% - increases with extroversion, reduces with age
        thisAgent->aStats->health/20 + thisAgent->aStats->happiness/20 + thisAgent->aStats->wealth/20 // reproduce - max 15% - increases with wealth, health and happiness
    };

    std::vector<int> choice_probability_prefix = {choice_probability[0]};
    for (int i = 1; i < choice_probability.size(); i++)
        choice_probability_prefix[i] = choice_probability_prefix[i-1] + choice_probability[i];

    int choice = (this->mt() % 100);
    // talk, insult, work with, hurt, party, reproduce
    if (choice < choice_probability_prefix[0])
        this->interact_talk(thisAgent, occupied, nearby_unoccupied_agents);
    else if (choice < choice_probability_prefix[1])
        this->interact_insult(thisAgent, occupied, nearby_unoccupied_agents);
    else if (choice < choice_probability_prefix[2])
        this->interact_work(thisAgent, occupied, nearby_unoccupied_agents);
    else if (choice < choice_probability_prefix[3])
        this->interact_hurt(thisAgent, occupied, nearby_unoccupied_agents);
    else if (choice < choice_probability_prefix[4])
        this->interact_party(thisAgent, occupied, nearby_unoccupied_agents);
    else if (choice < choice_probability_prefix[5])
        this->interact_reproduce(thisAgent, occupied, nearby_unoccupied_agents);
    else
        this->interact_idle(thisAgent);
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

    for (std::pair<int, Agent*> agent : Agent::AgentList)
        agent.second->grow();
}

Interaction_Manager::Interaction_Manager()
{
    instance = this;
    cur_day = 1;
    cur_year = 1;
    this->mt = std::mt19937(static_cast<int>(std::time(0)));;
}

Interaction_Manager* Interaction_Manager::instance {nullptr};

void Interaction_Manager::interact_talk(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents)
{
    std::cout << "talk\n";
    // make a list of 5 closest unoccupied people and choose randomly based off distance
    int sz = std::min((int) nearby_unoccupied_agents.size(), 5);
    int totalDist {0};
    for (int i = 0; i < sz; i++)
        totalDist += nearby_unoccupied_agents[i].first;

    int totalChoice {0};
    for (int i = 0; i < sz; i++)
    {
        // std::cout << "divide by: " << nearby_unoccupied_agents[i].first << std::endl; 
        totalChoice += totalDist/nearby_unoccupied_agents[i].first;
    }

    // std::cout << "choice: " << totalChoice << std::endl;
    int choice = mt() % totalChoice;
    int i = 0;
    while (choice > totalDist/nearby_unoccupied_agents[i].first)
    {
        choice -= totalDist/nearby_unoccupied_agents[i].first;
        i++;
    }

    Agent* otherAgent = Agent::AgentList[nearby_unoccupied_agents[i].second];
    

    // increase happiness and love
    int modifier = (1 + mt() % 3); // 1 - 3
    thisAgent->aStats->happiness = std::min(thisAgent->aStats->happiness + 3*modifier, 100);
    otherAgent->aStats->happiness = std::min(otherAgent->aStats->happiness + 3*modifier, 100);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].love = std::min(Agent::RelationshipMap[thisAgent->id][otherAgent->id].love + modifier, 100);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].love = std::min(Agent::RelationshipMap[otherAgent->id][thisAgent->id].love + modifier, 100);

    int newPosX = (thisAgent->posX + otherAgent->posX)/2;
    int newPosY = (thisAgent->posY + otherAgent->posY)/2;

    thisAgent->posX = newPosX;
    thisAgent->posY = newPosY;
    
    otherAgent->posX = newPosX;
    otherAgent->posY = newPosY;

    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Talked to " << otherAgent->name << std::endl;
    agentFile.close();

    agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
    agentFile << "Talked to " << thisAgent->name << std::endl;
    agentFile.close();

    std::cout << "talk completed\n";
}

void Interaction_Manager::interact_insult(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents)
{
    std::cout << "insult\n";
    // make a list of 10 closest unoccupied people and choose randomly based off least love + respect
    int sz = std::min((int) nearby_unoccupied_agents.size(), 10);
    
    int total_anti_love_respect {0};
    for (int i = 0; i < sz; i++)
        total_anti_love_respect += 201 - (Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].love + Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].respect);

    int choice = mt() % total_anti_love_respect;
    int i = 0;
    int cur_anti_love_respect = 201 - (Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].love + Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].respect);
    while (choice > cur_anti_love_respect)
    {
        choice -= cur_anti_love_respect;
        i++;
        cur_anti_love_respect = 201 - (Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].love + Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].respect);
    }

    Agent* otherAgent = Agent::AgentList[nearby_unoccupied_agents[i].second];

    // modify happiness, reduce love and respect
    int modifier = (1 + mt() % 3); // 1 - 3
    thisAgent->aStats->happiness = std::min(thisAgent->aStats->happiness + 2*modifier, 100);
    otherAgent->aStats->happiness = std::max(otherAgent->aStats->happiness - 3*modifier, 0);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].love = std::max(Agent::RelationshipMap[thisAgent->id][otherAgent->id].love - modifier, 0);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].love = std::max(Agent::RelationshipMap[otherAgent->id][thisAgent->id].love - modifier, 0);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect = std::max(Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect - modifier, 0);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect = std::max(Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect - modifier, 0);

    thisAgent->posX = otherAgent->posX;
    thisAgent->posY = otherAgent->posY;

    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Insulted " << otherAgent->name << std::endl;
    agentFile.close();

    agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
    agentFile << "Insulted by " << thisAgent->name << std::endl;
    agentFile.close();

    std::cout << "insult completed\n";
}

void Interaction_Manager::interact_work(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents)
{
    std::cout << "work\n";
    // make a list of 10 closest unoccupied people and choose randomly based off respect + wealth
    int sz = std::min((int) nearby_unoccupied_agents.size(), 10);
    
    int total_resp_wealth {0};
    for (int i = 0; i < sz; i++)
    {
        Agent* tmpA = Agent::AgentList[nearby_unoccupied_agents[i].second];
        Relationship tmpR = Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second];
        total_resp_wealth += tmpA->aStats->wealth + tmpR.respect;
    }

    int choice = mt() % total_resp_wealth;
    int i = 0;
    Agent* tmpA = Agent::AgentList[nearby_unoccupied_agents[i].second];
    Relationship tmpR = Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second];
    int cur_resp_wealth = tmpA->aStats->wealth + tmpR.respect;
    while (choice > cur_resp_wealth)
    {
        choice -= cur_resp_wealth;
        i++;
        tmpA = Agent::AgentList[nearby_unoccupied_agents[i].second];
        tmpR = Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second];
        cur_resp_wealth = tmpA->aStats->wealth + tmpR.respect;
    }

    Agent* otherAgent = Agent::AgentList[nearby_unoccupied_agents[i].second];

    // modify wealth, respect
    int modifier = (1 + mt() % 3); // 1 - 3
    thisAgent->aStats->wealth = std::min(thisAgent->aStats->wealth + 2*modifier, 100);
    otherAgent->aStats->wealth = std::min(otherAgent->aStats->wealth + 2*modifier, 100);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect = std::min(Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect + modifier, 100);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect = std::min(Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect + modifier, 100);

    int newPosX = (thisAgent->posX + otherAgent->posX)/2;
    int newPosY = (thisAgent->posY + otherAgent->posY)/2;

    thisAgent->posX = newPosX;
    thisAgent->posY = newPosY;
    
    otherAgent->posX = newPosX;
    otherAgent->posY = newPosY;

    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Worked with " << otherAgent->name << std::endl;
    agentFile.close();

    agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
    agentFile << "Worked with " << thisAgent->name << std::endl;
    agentFile.close();

    std::cout << "work completed\n";
}

void Interaction_Manager::interact_hurt(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents)
{
    std::cout << "hurt\n";
    // make a list of 20 closest unoccupied people and choose randomly based off least love + respect
    int sz = std::min((int) nearby_unoccupied_agents.size(), 20);
    
    int total_anti_love_respect {0};
    for (int i = 0; i < sz; i++)
        total_anti_love_respect += 201 - (Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].love + Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].respect);

    int choice = mt() % total_anti_love_respect;
    int i = 0;
    while (choice > 201 - (Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].love + Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].respect))
    {
        choice -= 201 - (Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].love + Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].respect);
        i++;
    }

    Agent* otherAgent = Agent::AgentList[nearby_unoccupied_agents[i].second];

    // modify happiness, reduce love, respect + health of other
    int modifier = (1 + mt() % 3); // 1 - 4
    thisAgent->aStats->happiness = std::min(thisAgent->aStats->happiness + 3*modifier, 100);
    otherAgent->aStats->happiness = std::max(otherAgent->aStats->happiness - 3*modifier, 0);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].love = std::max(Agent::RelationshipMap[thisAgent->id][otherAgent->id].love - modifier, 0);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].love = std::max(Agent::RelationshipMap[otherAgent->id][thisAgent->id].love - modifier, 0);

    Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect = std::max(Agent::RelationshipMap[thisAgent->id][otherAgent->id].respect - modifier, 0);
    Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect = std::max(Agent::RelationshipMap[otherAgent->id][thisAgent->id].respect - modifier, 0);

    otherAgent->aStats->health = std::max(otherAgent->aStats->health - modifier, 0);

    thisAgent->posX = otherAgent->posX;
    thisAgent->posY = otherAgent->posY;

    std::ofstream agentFile;
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Hurt " << otherAgent->name << std::endl;
    agentFile.close();

    agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
    agentFile << "Hurt by " << thisAgent->name << std::endl;
    agentFile.close();

    std::cout << "hurt completed\n";
}

void Interaction_Manager::interact_party(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents)
{
    std::cout << "party\n";
    // make a list of k closest unoccupied people based off extroversion - invite all - they reply randomly based on their extroversion and love for me
    int sz = std::min((int) nearby_unoccupied_agents.size(), 1 + thisAgent->aTraits->extrovertedness/5);
    
    
    std::vector<Agent*> attendingGuests {thisAgent};

    for (int i = 0; i < sz; i++)
    {
        Agent* otherAgent = Agent::AgentList[nearby_unoccupied_agents[i].second];
        if (mt() % 200 < otherAgent->aTraits->extrovertedness + Agent::RelationshipMap[otherAgent->id][thisAgent->id].love)
            attendingGuests.push_back(otherAgent);
    }

    // printf("failing here!\n");
    if (attendingGuests.size() < 2)
    {
        std::cout << "party failed";
        int modifier = 1 + mt() % 5;
        thisAgent->aTraits->extrovertedness = std::max(thisAgent->aTraits->extrovertedness - modifier, 0);
        std::ofstream agentFile;
        agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
        agentFile << "Party failed - no one attended" << attendingGuests.size() << std::endl;
        agentFile.close();
        return;
    }

    int tot_ext {0};
    int tot_love {0};

    for (int i = 0; i < attendingGuests.size(); i++)
    {
        tot_ext += attendingGuests[i]->aTraits->extrovertedness;
        for (int j = 0; j < attendingGuests.size(); j++)
        {
            if (i == j) continue;
            tot_love += Agent::RelationshipMap[attendingGuests[i]->id][attendingGuests[j]->id].love;
        }
    }


    int avg_ext = tot_ext/attendingGuests.size();
    int avg_love = tot_love/(attendingGuests.size()*attendingGuests.size() - attendingGuests.size());
    int modifier = (1 + (mt() % 2)) * (avg_ext + avg_love)/30; // 0 - 12

    // printf("failing in loop!\n");

    for (int i = 0; i < attendingGuests.size(); i++)
    {
        attendingGuests[i]->aStats->happiness = std::min(attendingGuests[i]->aStats->happiness + modifier, 100);
        for (int j = 0; j < attendingGuests.size(); j++)
        {
            if (i == j) continue;
            Agent::RelationshipMap[attendingGuests[i]->id][attendingGuests[j]->id].love = std::min(Agent::RelationshipMap[attendingGuests[i]->id][attendingGuests[j]->id].love + modifier, 100);
        }

        if (i == 0)
        {
            std::ofstream agentFile;
            agentFile.open("../logs/"+attendingGuests[i]->name+".txt", std::ios::app);
            agentFile << "Hosted party for " << attendingGuests.size() << std::endl;
            agentFile.close();
        }
        else
        {
            std::ofstream agentFile;
            agentFile.open("../logs/"+attendingGuests[i]->name+".txt", std::ios::app);
            agentFile << "Attended party by " << attendingGuests[0]->name << std::endl;
            agentFile.close();
        }
    }


    std::cout << "party completed\n";
}

void Interaction_Manager::interact_reproduce(Agent* thisAgent, std::set<int>& occupied, std::vector<std::pair<int, int>>& nearby_unoccupied_agents)
{
    std::cout << "reproduce attempt\n";

    // make a list of 5 closest unoccupied agents of opposite gender double random dice roll
    int sz = 0;
    std::vector<std::pair<int, int>> possible_mates; // love, id
    for (int i = 0; i < nearby_unoccupied_agents.size() && sz < 5; i++)
    {
        if (Agent::AgentList[nearby_unoccupied_agents[i].second]->aStats->gender ^ thisAgent->aStats->gender)
        {
            possible_mates.push_back({Agent::RelationshipMap[thisAgent->id][nearby_unoccupied_agents[i].second].love, nearby_unoccupied_agents[i].second});
            sz++;
        }
    }

    if (!possible_mates.size())
    {
        std::cout << "reproduce failed\n";
        std::ofstream agentFile;
        agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
        agentFile << "Reproduction failed - no mate." << std::endl;
        agentFile.close();
        return;
    }

    int totalLove {0};
    for (int i = 0; i < sz; i++)
    {
        totalLove += 1 + possible_mates[i].first;
    }

    // std::cout << "choice: " << totalLove << std::endl;
    int choice = mt() % totalLove;
    int i = 0;
    while (choice > 1 + possible_mates[i].first)
    {
        choice -= 1 + possible_mates[i].first;
        i++;
    }

    Agent* otherAgent = Agent::AgentList[nearby_unoccupied_agents[i].second];

    int otherLove = Agent::RelationshipMap[otherAgent->id][thisAgent->id].love;
    // std::cout << "issue here" << std::endl;
    if (thisAgent->aStats->age > 30 && otherAgent->aStats->age > 30 && abs(thisAgent->aStats->age - otherAgent->aStats->age) < 30 && (mt() % 50 > 101 - otherLove))
    {
        Agent* child = new Agent(mt);
        int modifier = 5 + mt() % 10;
        thisAgent->aStats->happiness = std::min(thisAgent->aStats->happiness + modifier, 100);
        otherAgent->aStats->happiness = std::min(otherAgent->aStats->happiness + modifier, 100);

        thisAgent->aStats->health = std::min(thisAgent->aStats->health + modifier/3, 100);
        otherAgent->aStats->health = std::min(otherAgent->aStats->health + modifier/3, 100);

        thisAgent->aStats->wealth = std::max(thisAgent->aStats->wealth - modifier, 0);
        otherAgent->aStats->wealth = std::max(otherAgent->aStats->wealth - modifier, 0);

        Agent::RelationshipMap[thisAgent->id][otherAgent->id].love = std::min(Agent::RelationshipMap[thisAgent->id][otherAgent->id].love + modifier, 100);
        Agent::RelationshipMap[otherAgent->id][thisAgent->id].love = std::min(Agent::RelationshipMap[otherAgent->id][thisAgent->id].love + modifier, 100);


        int newPosX = (thisAgent->posX + otherAgent->posX)/2;
        int newPosY = (thisAgent->posY + otherAgent->posY)/2;

        thisAgent->posX = newPosX;
        thisAgent->posY = newPosY;
        
        otherAgent->posX = newPosX;
        otherAgent->posY = newPosY;  
            
        std::ofstream agentFile;
        agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
        agentFile << "Birthed " << child->name << " with " << otherAgent->name << std::endl;
        agentFile.close();

        agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
        agentFile << "Birthed " << child->name << " with " << thisAgent->name << std::endl;
        agentFile.close();

        std::cout << "successfully reproduced\n";      
    }
    else
    {
        int modifier = 3 + mt() % 5;
        Agent::RelationshipMap[thisAgent->id][otherAgent->id].love = std::max(Agent::RelationshipMap[thisAgent->id][otherAgent->id].love - modifier, 0);

        std::ofstream agentFile;
        agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
        agentFile << "Rejected by " << otherAgent->name << std::endl;
        agentFile.close();

        agentFile.open("../logs/"+otherAgent->name+".txt", std::ios::app);
        agentFile << "Rejected " << thisAgent->name << std::endl;
        agentFile.close();

        std::cout << "rejected\n";      
    }
}

void Interaction_Manager::interact_idle(Agent* thisAgent)
{
    std::ofstream agentFile;
    int modifier = mt() % 6;
    if (modifier == 0)
    {
        thisAgent->aStats->wealth--;
        thisAgent->aStats->happiness--;
    }
    modifier = mt() % 20;
    if (modifier == 0)
        thisAgent->aStats->health++;

    thisAgent->posX += (mt() % 11) - 5;
    thisAgent->posY += (mt() % 11) - 5;
    thisAgent->posX = std::max(thisAgent->posX, 0);
    thisAgent->posX = std::min(thisAgent->posX, Agent::GRID_WIDTH);
    thisAgent->posY = std::max(thisAgent->posY, 0);
    thisAgent->posY = std::min(thisAgent->posY, Agent::GRID_HEIGHT);
    agentFile.open("../logs/"+thisAgent->name+".txt", std::ios::app);
    agentFile << "Idled" << std::endl;
    agentFile.close();
}