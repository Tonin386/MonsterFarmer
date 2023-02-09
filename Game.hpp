#ifndef GAME_HPP
#define GAME_HPP

#include "entities/items/Item.hpp"
#include "gameMethods/Farm.hpp"
#include "gameMethods/Fight.hpp"

#include <vector>

class Game
{
protected:
    std::vector<Monster *> _monsterTemplates;
    std::vector<Item *> _itemTemplates;

    std::vector<Monster*> _activeMonsters;
    std::vector<Item*> _activeItems;

    std::vector<Fight *> _fights;
    Farm *_farm;

public:
    Game();
    Game(std::vector<Monster *> m, std::vector<Item *> i);

    virtual std::vector<Monster *> getMonsterTemplates() const;
    virtual std::vector<Monster *> getMonsterTemplatesByRarity(int rarity);
    virtual std::vector<Item *> getItemTemplates() const;

    virtual std::vector<Monster*> getActiveMonsters() const;
    virtual std::vector<Item*> getActiveItems() const;

    virtual void addMonsterTemplate(Monster *m);
    virtual void addItemTemplate(Item *i);

    virtual void addActiveMonster(Monster* m);
    virtual void addActiveItem(Item* i);

    virtual int loadMonsterTemplates();
    virtual int loadActiveMonsters();

    virtual void startFight(Team *m1, Team *m2);
    virtual void startSummoning(int count);

    ~Game();
};

#endif