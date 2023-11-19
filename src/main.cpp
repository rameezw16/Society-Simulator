#include "Agent.cpp"

int Agent::count = 0;

std::mt19937 mt(static_cast<int>(std::time(0)));

int main()
{
    Agent("bob", mt);
    Agent("rob", mt);
}