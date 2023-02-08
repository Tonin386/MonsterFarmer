#include "Fight.hpp"

Fight::Fight(Monster* m1, Monster* m2) : _m1(m1), _m2(m2)
{
    _turnCount = 0;
}

bool Fight::playTurn()
{
    if(_turnCount % 2)
    {
        _m1->attack(_m2);
    }
    else
    {
        _m2->attack(_m1);
    }
    _turnCount++;

    return _m1->isAlive() && _m2->isAlive(); //Returns false if fight has ended
}

Fight::~Fight() {}
