#include "Farm.hpp"

Farm::Farm(/* args */) {}

int Farm::summonMonster()
{
    int tier = rand() % 1000;

    return tier;
}

Farm::~Farm()
{
}
