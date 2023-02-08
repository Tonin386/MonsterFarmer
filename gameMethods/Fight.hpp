#ifndef FIGHT_HPP
#define FIGHT_HPP

#include "../entities/Team.hpp"
#include "../frontend/TextInterface.hpp"
#include <map>

class Fight
{
protected:
    int _turnCount;
    std::map<int, int> _attacksCount;
    std::map<int, double> _damageDealt;
    Team* _attackers;
    Team* _defenders;
    std::vector<Monster*> _all;
public:
    Fight(Team* a, Team* d);

    virtual bool playTurn();
    virtual void showStats();

    ~Fight();
};

#endif