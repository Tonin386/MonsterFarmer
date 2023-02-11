#ifndef TEAM_HPP
#define TEAM_HPP

#include <vector>

class Monster;

class Team
{
protected:
    std::vector<Monster *> _monsters;
    int _currentTeamSize;

public:
    Team();

    virtual void addMonster(Monster *m);
    virtual void removeMonster(Monster *m);

    virtual bool hasLost() const;

    virtual Monster *getMonster(int id) const;
    virtual std::vector<Monster *> getMonsters() const;

    virtual Monster *operator[](int i);

    ~Team();
};

#endif