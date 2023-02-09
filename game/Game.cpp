#include "Game.hpp"

#include "../views/TextInterface.hpp"
#include "../libraries/json.hpp"

#include <fstream>

using namespace std;

Game::Game()
{
    _farm = new Farm();
}

Game::Game(vector<Monster *> m, vector<Item *> i) : _activeMonsters(m), _activeItems(i)
{
    _farm = new Farm();
}

vector<Monster *> Game::getMonsterTemplates() const
{
    return _monsterTemplates;
}

vector<Monster *> Game::getMonsterTemplatesByRarity(int rarity)
{
    vector<Monster*> monsters;
    for(int i = 0; i < _monsterTemplates.size(); i++)
    {
        if(_monsterTemplates[i]->getRarity() == rarity)
            monsters.push_back(_monsterTemplates[i]);
    }

    return monsters;
}

vector<Item *> Game::getItemTemplates() const
{
    return _itemTemplates;
}

vector<Monster*> Game::getActiveMonsters() const
{
    return _activeMonsters;
}

vector<Item*> Game::getActiveItems() const
{
    return _activeItems;
}

void Game::addMonsterTemplate(Monster *m)
{
    _monsterTemplates.push_back(m);
}

void Game::addItemTemplate(Item *i)
{
    _itemTemplates.push_back(i);
}

void Game::addActiveMonster(Monster* m)
{
    _activeMonsters.push_back(m);
    int id = _activeMonsters.size();
    m->setId(id);
}

void Game::addActiveItem(Item* i)
{
    _activeItems.push_back(i);
}

int Game::loadMonsterTemplates()
{
    using json = nlohmann::json;
    int monstersLoaded = 0;
    int monsterRange = 95;

    for(int i = 0; i < monsterRange; i++)
    {
        string filePath = "data/base_monsters/monster_" + to_string(i) + ".json";
        ifstream file(filePath);

        json j = json::parse(file);


        string name = j["name"].get<string>();
        int rarity = j["rarity"].get<int>();
        double baseAtk = j["baseAttack"].get<double>();
        double baseMaxHp = j["baseMaxHp"].get<double>();
        double baseSpeed = j["baseSpeed"].get<double>();
        double atkGrowth = j["attackGrowth"].get<double>();
        double maxHpGrowth = j["maxHpGrowth"].get<double>();
        double speedGrowth = j["speedGrowth"].get<double>();
        double maxStamina = j["maxStamina"].get<double>();
        double stamina = j["stamina"].get<double>();
        double xp = j["xp"].get<double>();

        Monster *m = new Monster(name, rarity, baseAtk, baseMaxHp, baseSpeed, atkGrowth, maxHpGrowth, speedGrowth, maxStamina, stamina, xp);
        addMonsterTemplate(m);
        monstersLoaded++;
    }

    return monstersLoaded;
}

int Game::loadActiveMonsters()
{
    return 0;
}

void Game::startFight(Team *attackers, Team *defenders)
{
    Fight *f = new Fight(attackers, defenders);
    _fights.push_back(f);

    TextInterface::log("New fight has started between two teams.");

    while (f->playTurn())
    {
        // TextInterface::log("Turn ended.");
    }

    TextInterface::log("Done.");
    TextInterface::showStats(f);
}

void Game::startSummoning(int count)
{
    vector<Monster*> legends = getMonsterTemplatesByRarity(5);
    vector<Monster*> epics = getMonsterTemplatesByRarity(4);
    vector<Monster*> rares = getMonsterTemplatesByRarity(3);
    vector<Monster*> uncommons = getMonsterTemplatesByRarity(2);
    vector<Monster*> commons = getMonsterTemplatesByRarity(1);

    for (int i = 0; i < count; i++)
    {
        Monster *m;
        int tier = _farm->summonMonster();
        if (tier < 10)
        {
            TextInterface::log("***** Legendary monster summoned! *****");
            m = new Monster(legends[rand() % legends.size()]);
        }
        else if (tier > 10 && tier <= 60)
        {
            TextInterface::log("**** Epic monster summoned! ****");
            m = new Monster(epics[rand() % epics.size()]);
        }
        else if (tier > 60 && tier <= 170)
        {
            TextInterface::log("*** Rare monster summoned! ***");
            m = new Monster(rares[rand() % rares.size()]);
        }
        else if (tier > 170 && tier <= 400)
        {
            TextInterface::log("** Uncommon monster summoned! **");
            m = new Monster(uncommons[rand() % uncommons.size()]);
        }
        else
        {
            TextInterface::log("* Common monster summoned! *");
            m = new Monster(commons[rand() % commons.size()]);
        }

        addActiveMonster(m);
        TextInterface::showStats(m);
    }
}

Game::~Game()
{
}
