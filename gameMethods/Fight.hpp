#ifndef FIGHT_HPP
#define FIGHT_HPP

#include "../entities/Monster.hpp"

class Fight
{
protected:
    int _turnCount;
    Monster* _m1;
    Monster* _m2;
public:
    Fight(Monster* m1, Monster* m2);

    virtual bool playTurn();

    ~Fight();
};

#endif