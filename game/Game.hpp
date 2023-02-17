#ifndef GAME_HPP
#define GAME_HPP

#include <vector>

class Monster;
class Item;
class Player;
class Fight;
class Farm;
class Team;

class Game
{
protected:
    std::vector<Monster *> _monsterTemplates;
    std::vector<Item *> _itemTemplates;

    std::vector<Monster *> _activeMonsters;
    std::vector<Item *> _activeItems;

    std::vector<Fight *> _fights;
    Farm *_farm;

    Player *_player;

public:
    Game();
    Game(std::vector<Monster *> m, std::vector<Item *> i);

    virtual std::vector<Monster *> getMonsterTemplates() const;
    virtual std::vector<Monster *> getMonsterTemplatesByRarity(int rarity);

    virtual std::vector<Monster *> getTanksTemplates();
    virtual std::vector<Monster *> getDamagesTemplates();
    virtual std::vector<Monster *> getHealersTemplates();

    virtual std::vector<Item *> getItemTemplates() const;
    virtual std::vector<Item *> getItemTemplatesByRarity(int rarity);

    virtual std::vector<Monster *> getActiveMonsters() const;
    virtual std::vector<Item *> getActiveItems() const;

    virtual void addMonsterTemplate(Monster *m);
    virtual void addItemTemplate(Item *i);

    virtual void addActiveMonster(Monster *m);
    virtual void addActiveItem(Item *i);

    virtual void setPlayer(Player *p);

    virtual int loadMonsterTemplates();
    virtual int loadActiveMonsters();

    virtual int loadItemTemplates();
    virtual int loadActiveItems();

    virtual void startFight(Team *m1, Team *m2);

    virtual std::vector<Monster *> summonMonsters(int count = 1);
    virtual std::vector<Item *> obtainItems(int count = 1);
    virtual Team *generateTeam(double level);

    ~Game();
};

#endif