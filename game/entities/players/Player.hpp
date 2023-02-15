#ifndef PLAYER_CPP
#define PLAYER_CPP

#include <vector>
#include <string>

class Game;
class Monster;
class Team;
class Item;

class Player
{
protected:
    std::vector<Item *> _items;
    std::vector<Monster *> _monsters;
    std::vector<Team *> _teams;
    std::string _name;
    Game *_game;

public:
    Player(std::string name);

    virtual std::string getName() const;
    virtual void setName(std::string name);
    virtual std::vector<Monster *> getMonsters() const;
    virtual std::vector<Team *> getTeams() const;
    virtual Team *getTeam(int team) const;

    virtual void addMonster(Monster *m);
    virtual void addItem(Item *i);

    virtual int generateTeams();
    virtual void summonMonsters(int count);
    virtual void obtainItems(int count);

    virtual void saveState();
    virtual void loadState();

    virtual void setGame(Game *g);

    ~Player();
};

#endif