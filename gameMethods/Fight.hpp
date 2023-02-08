#ifndef FIGHT_HPP
#define FIGHT_HPP

#include "../entities/Team.hpp"
#include <algorithm>

class Fight
{
protected:
    int _turnCount;
    Team* _attackers;
    Team* _defenders;
    std::vector<Monster*> _all;
public:
    Fight(Team* a, Team* d);

    virtual bool playTurn();

    ~Fight();
};

#endif