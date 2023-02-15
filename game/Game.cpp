#include "Game.hpp"

#include "../views/TextInterface.hpp"
#include "entities/monsters/Monster.hpp"
#include "entities/monsters/Team.hpp"
#include "entities/players/Player.hpp"
#include "entities/items/Item.hpp"
#include "scenarios/Farm.hpp"
#include "scenarios/Fight.hpp"
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
    vector<Monster *> monsters;
    for (int i = 0; i < _monsterTemplates.size(); i++)
    {
        if (_monsterTemplates[i]->getRarity() == rarity)
            monsters.push_back(_monsterTemplates[i]);
    }

    return monsters;
}

vector<Monster *> Game::getTanksTemplates()
{
    vector<Monster *> monsters;
    for (int i = 0; i < _monsterTemplates.size(); i++)
    {
        if (_monsterTemplates[i]->getType() == Monster::TANKER)
            monsters.push_back(_monsterTemplates[i]);
    }

    return monsters;
}

vector<Monster *> Game::getDamagesTemplates()
{
    vector<Monster *> monsters;
    for (int i = 0; i < _monsterTemplates.size(); i++)
    {
        if (_monsterTemplates[i]->getType() == Monster::DAMAGE)
            monsters.push_back(_monsterTemplates[i]);
    }

    return monsters;
}

vector<Monster *> Game::getHealersTemplates()
{
    vector<Monster *> monsters;
    for (int i = 0; i < _monsterTemplates.size(); i++)
    {
        if (_monsterTemplates[i]->getType() == Monster::HEALER)
            monsters.push_back(_monsterTemplates[i]);
    }

    return monsters;
}

vector<Item *> Game::getItemTemplates() const
{
    return _itemTemplates;
}

vector<Item*> Game::getItemTemplatesByRarity(int rarity)
{
    vector<Item *> items;
    for (int i = 0; i < _itemTemplates.size(); i++)
    {
        if (_itemTemplates[i]->getRarity() == rarity)
            items.push_back(_itemTemplates[i]);
    }

    return items;
}

vector<Monster *> Game::getActiveMonsters() const
{
    return _activeMonsters;
}

vector<Item *> Game::getActiveItems() const
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

void Game::addActiveMonster(Monster *m)
{
    _activeMonsters.push_back(m);
    int id = _activeMonsters.size();
    m->setId(id);
}

void Game::addActiveItem(Item *i)
{
    _activeItems.push_back(i);
    if(i->getId() == -1)
    {
        int maxId = _activeItems.size();
        for (int j = 0; j < _activeItems.size(); j++)
        {
            int itemId = _activeItems[j]->getId();
            if (itemId > maxId)
                maxId = itemId;
        }

        i->setId(maxId + 1);
    }
}

void Game::setPlayer(Player *p)
{
    _player = p;
    _player->setGame(this);
}

int Game::loadMonsterTemplates()
{
    using json = nlohmann::json;
    int monstersLoaded = 0;
    int monsterRange = 95;

    string filePath = "data/base_monsters/monsters.json";
    ifstream file(filePath);

    json j = json::parse(file);

    for (int i = 0; i < monsterRange; i++)
    {
        string name = j[i]["name"].get<string>();
        int rarity = j[i]["rarity"].get<int>();
        int type = j[i]["type"].get<int>();
        double baseAtk = j[i]["baseAttack"].get<double>();
        double baseMaxHp = j[i]["baseMaxHp"].get<double>();
        double baseSpeed = j[i]["baseSpeed"].get<double>();
        double atkGrowth = j[i]["attackGrowth"].get<double>();
        double maxHpGrowth = j[i]["maxHpGrowth"].get<double>();
        double speedGrowth = j[i]["speedGrowth"].get<double>();
        double maxStamina = j[i]["maxStamina"].get<double>();
        double stamina = j[i]["stamina"].get<double>();
        double xp = j[i]["xp"].get<double>();

        Monster *m = new Monster(name, rarity, type, baseAtk, baseMaxHp, baseSpeed, atkGrowth, maxHpGrowth, speedGrowth, maxStamina, stamina, xp);
        addMonsterTemplate(m);
        monstersLoaded++;
    }

    return monstersLoaded;
}

int Game::loadActiveMonsters()
{
    using json = nlohmann::json;
    int monstersLoaded = 0;

    string monstersFilePath = "save/monsters.json";
    string playerFilePath = "save/player.json";
    ifstream monstersFile(monstersFilePath);
    ifstream playerFile(playerFilePath);

    json jMonsters = json::parse(monstersFile);
    json jPlayer = json::parse(playerFile);

    int monsterRange = jPlayer["monsters"].get<int>();

    for (int i = 0; i < monsterRange; i++)
    {
        string name = jMonsters[i]["name"].get<string>();
        int rarity = jMonsters[i]["rarity"].get<int>();
        int type = jMonsters[i]["type"].get<int>();
        double baseAtk = jMonsters[i]["b_atk"].get<double>();
        double baseMaxHp = jMonsters[i]["b_maxHp"].get<double>();
        double baseSpeed = jMonsters[i]["b_speed"].get<double>();
        double atkGrowth = jMonsters[i]["g_atk"].get<double>();
        double maxHpGrowth = jMonsters[i]["g_maxHp"].get<double>();
        double speedGrowth = jMonsters[i]["g_speed"].get<double>();
        double maxStamina = jMonsters[i]["maxStamina"].get<double>();
        double stamina = jMonsters[i]["stamina"].get<double>();
        double xp = jMonsters[i]["xp"].get<double>();

        Monster *m = new Monster(name, rarity, type, baseAtk, baseMaxHp, baseSpeed, atkGrowth, maxHpGrowth, speedGrowth, maxStamina, stamina, xp);
        _player->addMonster(m);
        monstersLoaded++;
    }

    return monstersLoaded;
}

int Game::loadItemTemplates()
{
    using json = nlohmann::json;
    int itemsLoaded = 0;
    int itemRange = 100;

    string filePath = "data/base_items/items.json";
    ifstream file(filePath);

    json j = json::parse(file);
    for(int i = 0; i < itemRange; i++)
    {
        string name = j[i]["name"].get<string>();
        char type = j[i]["type"].get<string>()[0];
        int rarity = j[i]["rarity"].get<int>();
        double crit_rate = j[i]["crit_rate"].get<double>();
        double dodge_rate = j[i]["dodge_rate"].get<double>();
        double combo_rate = j[i]["combo_rate"].get<double>();
        double stun_rate = j[i]["stun_rate"].get<double>();
        int def_rating = j[i]["def_rating"].get<int>();

        Item *item = new Item(crit_rate, dodge_rate, combo_rate, stun_rate, def_rating, name, type, rarity);
        addItemTemplate(item);
        itemsLoaded++;
    }

    return itemsLoaded;
}

int Game::loadActiveItems()
{
    using json = nlohmann::json;
    int itemsLoaded = 0;

    string filePath = "save/items.json";
    ifstream file(filePath);
    
    json j = json::parse(file);

    string playerFilePath = "save/player.json";
    ifstream playerFile(playerFilePath);

    json jPlayer = json::parse(playerFile);
    int itemsCount = jPlayer["items"].get<int>();

    for(int i = 0; i < itemsCount; i++)
    {
        string name = j[i]["name"].get<string>();
        char type = j[i]["type"].get<char>();
        int rarity = j[i]["rarity"].get<int>();
        double crit_rate = j[i]["crit_rate"].get<double>();
        double dodge_rate = j[i]["dodge_rate"].get<double>();
        double combo_rate = j[i]["combo_rate"].get<double>();
        double stun_rate = j[i]["stun_rate"].get<double>();
        int def_rating = j[i]["def_rating"].get<int>();
        int id = j[i]["id"].get<int>();

        Item *item = new Item(crit_rate, dodge_rate, combo_rate, stun_rate, def_rating, name, type, rarity);
        item->setId(id);
        addActiveItem(item);
        itemsLoaded++;
    }

    return itemsLoaded;
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
    TextInterface::log(f);

    double coeff = 0.66;

    if (!f->getAttackers()->hasLost())
    {
        _player->summonMonsters(1);
        _player->obtainItems(2);
        coeff = 1.25;
    }

    double xp = (f->getDefendersRating() / f->getAttackersRating()) * f->getDefendersRating() * 10 * coeff;
    (*(f->getAttackers()))[0]->levelUp(xp);
    (*(f->getAttackers()))[1]->levelUp(xp);
    (*(f->getAttackers()))[2]->levelUp(xp);
    (*(f->getAttackers()))[3]->levelUp(xp);

    f->getAttackers()->prepareForNextFight();
    _player->generateTeams();
}

vector<Monster *> Game::summonMonsters(int count)
{
    vector<Monster *> legends = getMonsterTemplatesByRarity(5);
    vector<Monster *> epics = getMonsterTemplatesByRarity(4);
    vector<Monster *> rares = getMonsterTemplatesByRarity(3);
    vector<Monster *> uncommons = getMonsterTemplatesByRarity(2);
    vector<Monster *> commons = getMonsterTemplatesByRarity(1);

    vector<Monster *> monsters;

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

        monsters.push_back(m);
        TextInterface::log(m);
    }

    return monsters;
}

vector<Item*> Game::obtainItems(int count)
{
    vector<Item *> legends = getItemTemplatesByRarity(5);
    vector<Item *> epics = getItemTemplatesByRarity(4);
    vector<Item *> rares = getItemTemplatesByRarity(3);
    vector<Item *> uncommons = getItemTemplatesByRarity(2);
    vector<Item *> commons = getItemTemplatesByRarity(1);

    vector<Item *> items;

    for (int i = 0; i < count; i++)
    {
        Item *it;
        int tier = _farm->obtainItem();
        if (tier < 10)
        {
            TextInterface::log("***** Legendary Item summoned! *****");
            it = new Item(legends[rand() % legends.size()]);
        }
        else if (tier > 10 && tier <= 60)
        {
            TextInterface::log("**** Epic Item summoned! ****");
            it = new Item(epics[rand() % epics.size()]);
        }
        else if (tier > 60 && tier <= 170)
        {
            TextInterface::log("*** Rare Item summoned! ***");
            it = new Item(rares[rand() % rares.size()]);
        }
        else if (tier > 170 && tier <= 400)
        {
            TextInterface::log("** Uncommon Item summoned! **");
            it = new Item(uncommons[rand() % uncommons.size()]);
        }
        else
        {
            TextInterface::log("* Common Item summoned! *");
            it = new Item(commons[rand() % commons.size()]);
        }

        items.push_back(it);
        TextInterface::log(it);
    }

    return items;
    
}

Team *Game::generateTeam()
{
    vector<Monster *> monsters;
    int sizeMonsters;

    monsters = getTanksTemplates();
    sizeMonsters = monsters.size();
    Monster *t1 = new Monster(monsters[rand() % sizeMonsters]);
    Monster *t2 = new Monster(monsters[rand() % sizeMonsters]);

    monsters = getDamagesTemplates();
    sizeMonsters = monsters.size();
    Monster *d = new Monster(monsters[rand() % sizeMonsters]);

    monsters = getHealersTemplates();
    sizeMonsters = monsters.size();
    Monster *h = new Monster(monsters[rand() % sizeMonsters]);

    addActiveMonster(t1);
    addActiveMonster(t2);
    addActiveMonster(d);
    addActiveMonster(h);

    Team *t = new Team();
    t->addMonster(t1);
    t->addMonster(t2);
    t->addMonster(d);
    t->addMonster(h);

    return t;
}

Game::~Game()
{
}
