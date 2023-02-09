#include "Team.hpp"

using namespace std;

Team::Team()
{
    Monster *nullMonster = new Monster();
    _monsters.push_back(nullMonster);
    _monsters.push_back(nullMonster);
    _monsters.push_back(nullMonster);
    _monsters.push_back(nullMonster);

    _currentTeamSize = 0;
}

void Team::addMonster(Monster *m)
{
    if (_currentTeamSize < 4)
    {
        _monsters[_currentTeamSize] = m;
        _currentTeamSize++;
    }
    else
    {
        _monsters.erase(_monsters.begin());
        _monsters.push_back(m);
    }
}

void Team::removeMonster(Monster *m)
{
    for (int i = 0; i < 4; i++)
    {
        if (_monsters[i] == m)
        {
            _monsters.erase(_monsters.begin() + i);
            return;
        }
    }
}

bool Team::hasLost() const
{
    for (int i = 0; i < 4; i++)
    {
        if (_monsters[i]->isAlive())
            return false;
    }

    return true;
}

Monster *Team::getMonster(int id) const
{
    return _monsters[id];
}

vector<Monster *> Team::getMonsters() const
{
    return _monsters;
}

Monster *Team::operator[](int i)
{
    return _monsters[i % 4];
}

Team::~Team()
{
}