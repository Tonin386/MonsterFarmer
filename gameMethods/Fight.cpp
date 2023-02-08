#include "Fight.hpp"

Fight::Fight(Monster *m1, Monster *m2) : _m1(m1), _m2(m2)
{
    _turnCount = 0;
}

bool Fight::playTurn()
{
    _turnCount++;
    double s1 = _m1->getStamina();
    double s2 = _m2->getStamina();

    if (_m1->canPlay() && _m2->canPlay())
    {
        if (s1 >= s2)
        {
            _m1->attack(_m2);
            if (_m2->isAlive())
                _m2->attack(_m1);
        }
        else
        {
            _m2->attack(_m1);
            if (_m1->isAlive())
                _m1->attack(_m2);
        }
    }
    else if (_m1->canPlay())
    {
        _m1->attack(_m2);
        if (_m2->isAlive())
            _m2->prepare();
    }
    else if (_m2->canPlay())
    {
            _m2->attack(_m1);
            if (_m1->isAlive())
                _m1->prepare();
    }
    else
    {
        _m1->prepare();
        _m2->prepare();
    }

    return _m1->isAlive() && _m2->isAlive(); // Returns false if fight has ended
}

Fight::~Fight() {}
