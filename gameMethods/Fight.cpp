#include "Fight.hpp"
#include <queue>

using namespace std;

Fight::Fight(Team* a, Team* d) : _attackers(a), _defenders(d)
{
    _turnCount = 0;

    for(int i = 0; i<4; i++)
    {
        _all.push_back(_attackers->getMonsters()[i]);
        _all.push_back( _defenders->getMonsters()[i]);
        _all[i * 2]->setTeam(1);
        _all[i * 2 + 1]->setTeam(2);
    }
}

bool Fight::playTurn()
{
    sort(_all.begin(), _all.end());
    _turnCount++;
    // double s1 = _m1->getStamina();
    // double s2 = _m2->getStamina();

    // if (_m1->canPlay() && _m2->canPlay())
    // {
    //     if (s1 >= s2)
    //     {
    //         _m1->attack(_m2);
    //         if (_m2->isAlive())
    //             _m2->attack(_m1);
    //     }
    //     else
    //     {
    //         _m2->attack(_m1);
    //         if (_m1->isAlive())
    //             _m1->attack(_m2);
    //     }
    // }
    // else if (_m1->canPlay())
    // {
    //     _m1->attack(_m2);
    //     if (_m2->isAlive())
    //         _m2->prepare();
    // }
    // else if (_m2->canPlay())
    // {
    //         _m2->attack(_m1);
    //         if (_m1->isAlive())
    //             _m1->prepare();
    // }
    // else
    // {
    //     _m1->prepare();
    //     _m2->prepare();
    // }

    return _attackers->hasLost() || _defenders->hasLost();
}

Fight::~Fight() {}
