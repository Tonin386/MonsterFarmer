#ifndef GAME_HPP
#define GAME_HPP

#include "entities/items/Item.hpp"
#include "gameMethods/Farm.hpp"
#include "gameMethods/Fight.hpp"
#include "frontend/TextInterface.hpp"

#include <vector>

class Game
{
protected:
    std::vector<Monster*> _monsters;
    std::vector<Item*> _items;
    std::vector<Fight*> _fights;
    Farm* _farm;

public:
    Game();
    Game(std::vector<Monster*> m, std::vector<Item*> i);

    virtual std::vector<Monster*>   getMonsters()   const;
    virtual std::vector<Item*>      getItems()      const;

    virtual void addMonster(Monster* m);
    virtual void addItem(Item* i);

    virtual void startFight(Team* m1, Team* m2);
    virtual void startSummoning(int count);

    ~Game();
};


#endif