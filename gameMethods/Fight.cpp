#include "Fight.hpp"
#include <algorithm>

using namespace std;

Fight::Fight(Team *a, Team *d) : _attackers(a), _defenders(d)
{
    _turnCount = 0;

    for (int i = 0; i < 4; i++)
    {
        Monster *m1 = (*_attackers)[i];
        Monster *m2 = (*_defenders)[i];
        _all.push_back(m1);
        _all.push_back(m2);
        m1->setTeam(1);
        m2->setTeam(2);
        _attacksCount[m1->getId()] = 0;
        _attacksCount[m2->getId()] = 0;
        _damageDealt[m1->getId()] = 0;
        _damageDealt[m2->getId()] = 0;
    }
}

bool Fight::playTurn()
{
    sort(_all.begin(), _all.end(), [](const Monster *a, const Monster *b)
         { return a->getStamina() > b->getStamina(); });
    _turnCount++;

    for (int i = 0; i < 8; i++)
    {
        int id = _all[i]->getId();
        if (_all[i]->canPlay() && _all[i]->isAlive())
        {
            for (int j = 0; j < 4; j++) // We find the target of the attack
            {
                if (_all[i]->getTeam() == 1)
                {
                    if ((*_defenders)[j]->isAlive())
                    {
                        _attacksCount[id]++;
                        _damageDealt[id] += _all[i]->attack((*_defenders)[j]);
                        // TextInterface::log(_all[i]->getName() + " attacks " + (*_defenders)[j]->getName());
                        break;
                    }
                }
                else
                {
                    if ((*_attackers)[j]->isAlive())
                    {
                        _attacksCount[id]++;
                        _damageDealt[id] += _all[i]->attack((*_attackers)[j]);
                        // TextInterface::log(_all[i]->getName() + " attacks " + (*_attackers)[j]->getName());
                        break;
                    }
                }
            }
        }
        else if (_all[i]->isAlive()) // we must stack stamina to attack.
        {
            // TextInterface::log(_all[i]->getName() + " prepares. " + to_string(_all[i]->getStamina()) + "+" + to_string(_all[i]->getSpeed()) + "/" + to_string(_all[i]->getMaxStamina()));
            _all[i]->prepare();
        }
        else
        {
            // TextInterface::log(_all[i]->getName() + " is dead.");
        }
    }

    // int i;
    // cin >> i;

    return !(_attackers->hasLost() || _defenders->hasLost());
}

int Fight::getTurnCount() const
{
    return _turnCount;
}

map<int, int> Fight::getAttacksCount() const
{
    return _attacksCount;
}

map<int, double> Fight::getDamageDealt() const
{
    return _damageDealt;
}

Team* Fight::getAttackers() const
{
    return _attackers;
}

Team* Fight::getDefenders() const
{
    return _defenders;
}

vector<Monster*> Fight::getMonsters() const
{
    return _all;
}

Fight::~Fight() {}
