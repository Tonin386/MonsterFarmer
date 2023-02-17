#include "Team.hpp"
#include "Monster.hpp"

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

void Team::prepareForNextFight()
{
    _monsters[0]->reset();
    _monsters[1]->reset();
    _monsters[2]->reset();
    _monsters[3]->reset();
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

double Team::getAverageLevel()
{
    return (_monsters[0]->getLevel() + _monsters[1]->getLevel() + _monsters[2]->getLevel() + _monsters[3]->getLevel()) / 4;
}

double Team::getAverageRating()
{
    return (_monsters[0]->getRating() + _monsters[1]->getRating() + _monsters[2]->getRating() + _monsters[3]->getRating()) / 4;
}

double Team::getAverageItemsRating()
{
    return (_monsters[0]->getItemsRating() + _monsters[1]->getItemsRating() + _monsters[2]->getItemsRating() + _monsters[3]->getItemsRating()) / 4;
}

Monster *Team::operator[](int i)
{
    return _monsters[i % 4];
}

Team::~Team()
{
}