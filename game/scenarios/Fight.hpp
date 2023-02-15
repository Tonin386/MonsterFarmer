#ifndef FIGHT_HPP
#define FIGHT_HPP

#include <map>
#include <vector>

class Monster;
class Team;

class Fight
{
protected:
    int _turnCount;
    std::map<int, int> _attacksCount;
    std::map<int, double> _damageDealt;
    Team *_attackers;
    Team *_defenders;
    std::vector<Monster *> _all;

    bool _ended;

public:
    Fight(Team *a, Team *d);

    virtual bool playTurn();

    virtual bool hasEnded() const;

    virtual int getTurnCount() const;
    virtual std::map<int, int> getAttacksCount() const;
    virtual std::map<int, double> getDamageDealt() const;
    virtual Team* getAttackers() const;
    virtual double getAttackersRating();
    virtual Team* getDefenders() const;
    virtual double getDefendersRating();
    std::vector<Monster*> getMonsters() const;

    ~Fight();
};

#endif