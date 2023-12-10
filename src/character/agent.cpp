#include "../../include/characters/agent.h"

Agent::Agent(std::mt19937 &mt, const int spritesheet_pos_x,
             const int spritesheet_pos_y, std::string name, int posX, int posY)
    : Entity(posX, posY, spritesheet_pos_x, spritesheet_pos_y) {
  this->id = count++;
  if (name.length())
    this->name = name;
  else {
    std::string name;
    bool match = true;
    while (match) {
      match = false;
      name = fname_list[mt() % fname_list.size()] + " " +
             lname_list[mt() % lname_list.size()];
      for (std::pair<int, Agent *> agent : Agent::AgentList) {
        match |= (name == agent.second->name);
      }
    }
    this->name = name;
  }

  if (posX != -1)
    this->posX = posX;
  else
    this->posX = mt() % Agent::GRID_WIDTH;

  if (posY != -1)
    this->posY = posY;
  else
    this->posY = mt() % Agent::GRID_HEIGHT;

  this->aStats = new Stats(mt); // constructor has initialisation formulas
  this->aTraits =
      new Traits(mt, this->aStats); // constructor has initialisation formulas

  // Add details to file
  std::ofstream agentFile;
  agentFile.open("../logs/" + this->name + ".txt");
  agentFile << this->name << " created at (" << this->posX << ", " << this->posY
            << ") with id: " << this->id
            << ", gender: " << ((this->aStats->gender) ? "male" : "female")
            << ", age: " << this->aStats->age
            << ", health: " << this->aStats->health
            << ", wealth: " << this->aStats->wealth
            << ", happiness: " << this->aStats->happiness << "\n";
  agentFile << "and personality traits:  Openness: " << this->aTraits->openness
            << ", Conscientiousness: " << this->aTraits->conscientiousness
            << ", Extrovertedness: " << this->aTraits->extrovertedness
            << ", Agreeableness: " << this->aTraits->agreeableness
            << ", Neuroticism: " << this->aTraits->neuroticism << std::endl;
  agentFile.close();

  // add relations
  this->initialise_relations();

  // store Agent in list
  AgentList[this->id] = this;
}

void Agent::initialise_relations() {
  std::map<int, Relationship> this_relations;
  for (std::pair<int, Agent *> i : AgentList) {
    Agent *other = i.second;

    // Relation of this with other - based off stats and traits
    this_relations[other->id] =
        Relationship(this->aStats, this->aTraits, other->aStats);
    Relationship cur = this_relations[other->id];
    this->relationSum = this->relationSum + cur;

    // add to file
    printf("adding relation of %s with %s\n", this->name.c_str(),
           other->name.c_str());
    std::ofstream agentFile;
    agentFile.open("../logs/" + this->name + ".txt", std::ios::app);
    agentFile << "Towards " << other->name << " has Love: " << cur.love
              << ", Respect: " << cur.respect << std::endl;
    agentFile.close();

    // Relation of other with this - based off stats and traits
    RelationshipMap[other->id][this->id] =
        Relationship(other->aStats, other->aTraits, this->aStats);
    cur = RelationshipMap[other->id][this->id];
    other->relationSum = other->relationSum + cur;

    // add to file
    printf("adding relation of %s with %s\n", other->name.c_str(),
           this->name.c_str());
    agentFile.open("../logs/" + other->name + ".txt", std::ios::app);
    agentFile << "Towards " << this->name << " has Love: " << cur.love
              << ", Respect: " << cur.respect << std::endl;
    agentFile.close();
  }
  RelationshipMap[this->id] = this_relations;
}

void Agent::move_agent(int posX, int posY) {
  this->posX = posX;
  this->posY = posY;
  std::ofstream agentFile;
  agentFile.open("../logs/" + this->name + ".txt", std::ios::app);
  agentFile << "Moved to pos: (" << this->posX << ", " << this->posY << ")"
            << std::endl;
  agentFile.close();
}

void Agent::new_day(int year, int day) {
  std::ofstream agentFile;
  agentFile.open("../logs/" + this->name + ".txt", std::ios::app);
  agentFile << "Year: " << year << ", Day: " << day << std::endl;
  agentFile.close();
}

void Agent::grow() {
  this->aStats->age++;
  this->aStats->health -= (this->aStats->age) / 10;
}

void Agent::display_agent_list() {
  for (std::pair<int, Agent *> i : AgentList) {
    printf("%i, ", i.first);
  }
  printf("\n");
}

void Agent::display_relation_map() {
  for (std::pair<int, std::map<int, Relationship>> i : RelationshipMap) {
    for (std::pair<int, Relationship> j : i.second) {
      printf("%i -> %i\n", i.first, j.first);
    }
  }
  printf("\n");
}

// void Agent::is_dead() {
//   std::ofstream agentFile;
//   agentFile.open("../logs/" + this->name + ".txt", std::ios::app);
//   if (this->aStats->health <= 0) {
//     agentFile << "Died due to poor health" << std::endl;
//     agentFile.close();
//     delete this;
//   } else if (this->aStats->wealth <= 0) {
//     agentFile << "Died due to poverty" << std::endl;
//     agentFile.close();
//     delete this;
//   } else if (this->aStats->happiness <= 0) {
//     agentFile << "Died due to depression" << std::endl;
//     agentFile.close();
//     delete this;
//   }
//   if (agentFile.is_open())
//     agentFile.close();
// }

int Agent::get_social_factor(int avg_love)
{
  return ((avg_love - 20)  * (aTraits->extrovertedness - 30)) / 10;
}

bool Agent::is_dead() {
  std::ofstream agentFile;
  agentFile.open("../logs/" + this->name + ".txt", std::ios::app);
  if (this->aStats->health <= 0) {
    agentFile << "Died due to poor health" << std::endl;
    agentFile.close();
    return true;

  } else if (this->aStats->wealth <= 0) {
    agentFile << "Died due to poverty" << std::endl;
    agentFile.close();
    return true;

  } else if (this->aStats->happiness <= 0) {
    agentFile << "Died due to depression" << std::endl;
    agentFile.close();
    return true;
  }

  if (agentFile.is_open())
    agentFile.close();
  return false;
}

Agent::~Agent() {
  // display_agent_list();
  // display_relation_map();
  delete this->aStats;
  delete this->aTraits;
  RelationshipMap.erase(this->id);
  AgentList.erase(this->id);
  for (std::pair<int, Agent *> i : AgentList) {
    i.second->relationSum =
        i.second->relationSum - RelationshipMap[i.second->id][this->id];
    i.second->aStats->happiness = std::min(i.second->aStats->happiness +
        (40 - RelationshipMap[i.second->id][this->id].love) /
        3, 100); // sad to see loved one die - happy to see hated one die
    i.second->aStats->happiness = std::max(i.second->aStats->happiness, 0);
    RelationshipMap[i.second->id].erase(this->id);
  }
}

int Agent::count = 0;
std::map<int, Agent *> Agent::AgentList;
std::map<int, std::map<int, Relationship>> Agent::RelationshipMap;
std::vector<std::string> Agent::fname_list = {
    "John",        "Anna",     "Mark",        "Emma",    "Paul",    "Laura",
    "Alex",        "Grace",    "Michael",     "Olivia",  "William", "Ava",
    "Daniel",      "Sophia",   "Matthew",     "Ella",    "James",   "Lily",
    "Christopher", "Mia",      "Andrew",      "Chloe",   "David",   "Emily",
    "Benjamin",    "Abigail",  "Nicholas",    "Hannah",  "Joseph",  "Samantha",
    "Ethan",       "Victoria", "Christopher", "Evelyn",  "Daniel",  "Natalie",
    "Elijah",      "Madison",  "Gabriel",     "Avery",   "Nathan",  "Scarlett",
    "Logan",       "Grace",    "Brandon",     "Lillian", "Tyler",   "Addison"};
std::vector<std::string> Agent::lname_list = {
    "Smith",    "Johnson",  "Brown",     "Taylor",   "Jones",      "Miller",
    "Davis",    "Garcia",   "Rodriguez", "Martinez", "Hernandez",  "Lopez",
    "Gonzalez", "Williams", "Moore",     "Jackson",  "Lee",        "Perez",
    "Young",    "Allen",    "Hall",      "Tran",     "Wright",     "Scott",
    "Nguyen",   "Mitchell", "Evans",     "Carter",   "Turner",     "Parker",
    "Collins",  "Edwards",  "Stewart",   "Flores",   "Morales",    "Morris",
    "Murphy",   "Rivera",   "Cook",      "Fisher",   "Richardson", "Simmons",
    "Russell",  "Bryant",   "Alexander", "Tucker",   "Porter",     "Graham"};

int Agent::GRID_WIDTH = SIZE;
int Agent::GRID_HEIGHT = SIZE;

bool Agent::get_walkable() const { return this->walkable; };
std::string Agent::get_type() const { return this->type; };

void Agent::step(){};

void Agent::consume()
{
  if (this->aStats->health > 80)
    reproduction_factor = std::min(reproduction_factor + 3, 100);
  else
    this->aStats->health = std::min(this->aStats->health + 5, 100);
}

bool Agent::attempt_reproduce()
{
  if (reproduction_factor == 100)
  {
    reproduction_factor = 0;
    this->aStats->health = std::max(this->aStats->health - 30, 0);
    return true;
  }
  return false;
}

void Agent::decay()
{
  this->aStats->health = std::max(this->aStats->health - 10, 0);
}

void Agent::grow_back(){};
