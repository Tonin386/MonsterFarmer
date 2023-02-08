#include "Fight.hpp"
#include <queue>

using namespace std;

Fight::Fight(Team *a, Team *d) : _attackers(a), _defenders(d)
{
    _turnCount = 0;

    for (int i = 0; i < 4; i++)
    {
        _all.push_back((*_attackers)[i]);
        _all.push_back((*_defenders)[i]);
        (*_attackers)[i]->setTeam(1);
        (*_defenders)[i]->setTeam(2);
    }
}

bool Fight::playTurn()
{
    sort(_all.begin(), _all.end());
    _turnCount++;

    for (int i = 0; i < 8; i++)
    {
        if (_all[i]->canPlay() && _all[i]->isAlive())
        {
            for (int j = 0; j < 4; j++) //We find the target of the attack
            {
                if (_all[i]->getTeam() == 1)
                {
                    if ((*_defenders)[j]->isAlive())
                    {
                        _all[i]->attack((*_defenders)[j]);
                        break;
                    }
                }
                else
                {
                    if((*_attackers)[j]->isAlive())
                    {
                        _all[i]->attack((*_attackers)[j]);
                        break;
                    }
                }
            }
        }
        else if(_all[i]->isAlive()) //we must stack stamina to attack.
        { 
            _all[i]->prepare();
        }
    }

    return _attackers->hasLost() || _defenders->hasLost();
}

Fight::~Fight() {}
