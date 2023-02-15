#include "Farm.hpp"

Farm::Farm(/* args */) {}

int Farm::summonMonster()
{
    int tier = rand() % 1000;

    return tier;
}

int Farm::obtainItem()
{
    return rand() % 1000;
}

Farm::~Farm()
{
}
