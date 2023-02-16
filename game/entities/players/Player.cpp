#include "Player.hpp"

#include "../../Game.hpp"
#include "../../entities/monsters/Monster.hpp"
#include "../../entities/monsters/Team.hpp"
#include "../items/Item.hpp"

#include "../../../libraries/json.hpp"

#include <fstream>
#include <iostream>

using namespace std;

Player::Player(string name) : _name(name)
{
}

string Player::getName() const
{
    return _name;
}

void Player::setName(string name)
{
    _name = name;
}

vector<Monster *> Player::getMonsters() const
{
    return _monsters;
}

vector<Team *> Player::getTeams() const
{
    return _teams;
}

Team *Player::getTeam(int team) const
{
    return _teams[team];
}

void Player::addMonster(Monster *m)
{
    _monsters.push_back(m);
    _game->addActiveMonster(m);
}

void Player::addItem(Item *i)
{
    _game->addActiveItem(i);
    _items.push_back(i);
}

int Player::generateTeams()
{
    if (_monsters.size() < 4)
    {
        return 0;
    }

    int nbTankers = 0;
    vector<Monster *> tankers;

    int nbDamages = 0;
    vector<Monster *> damages;

    int nbHealers = 0;
    vector<Monster *> healers;

    int nbArmors = 0;
    vector<Item *> armors;

    int nbWeapons = 0;
    vector<Item *> weapons;

    int nbRings = 0;
    vector<Item *> rings;

    int nbTalismans = 0;
    vector<Item *> talismans;

    for (int i = 0; i < _monsters.size(); i++)
    {
        Monster *m = _monsters[i];
        switch (m->getType())
        {
        default:
        case Monster::TANKER:
            tankers.push_back(m);
            nbTankers++;
            break;
        case Monster::DAMAGE:
            damages.push_back(m);
            nbDamages++;
            break;
        case Monster::HEALER:
            healers.push_back(m);
            nbHealers++;
            break;
        }
    }

    for (int i = 0; i < _items.size(); i++)
    {
        Item *it = _items[i];
        switch (it->getType())
        {
        default:
            break;
        case Item::ARMOR_TYPE:
            armors.push_back(it);
            nbArmors++;
            break;
        case Item::WEAPON_TYPE:
            weapons.push_back(it);
            nbWeapons++;
            break;
        case Item::RING_TYPE:
            rings.push_back(it);
            nbRings++;
            break;
        case Item::TALISMAN_TYPE:
            talismans.push_back(it);
            nbTalismans++;
            break;
        }
    }

    if (nbTankers > 0)
        sort(tankers.begin(), tankers.end(), [](const Monster *a, const Monster *b)
             { return a->getRating() > b->getRating(); });

    if (nbDamages > 0)
        sort(damages.begin(), damages.end(), [](const Monster *a, const Monster *b)
             { return a->getRating() > b->getRating(); });

    if (nbHealers > 0)
        sort(healers.begin(), healers.end(), [](const Monster *a, const Monster *b)
             { return a->getRating() > b->getRating(); });

    if (nbArmors > 0)
        sort(armors.begin(), armors.end(), [](const Item *a, const Item *b)
             { return a->getRating() > b->getRating(); });

    if (nbWeapons > 0)
        sort(weapons.begin(), weapons.end(), [](const Item *a, const Item *b)
             { return a->getRating() > b->getRating(); });

    if (nbRings > 0)
        sort(rings.begin(), rings.end(), [](const Item *a, const Item *b)
             { return a->getRating() > b->getRating(); });

    if (nbTalismans > 0)
        sort(talismans.begin(), talismans.end(), [](const Item *a, const Item *b)
             { return a->getRating() > b->getRating(); });

    int nbTeams = 0;
    while (nbTankers > 2 && nbDamages > 1 && nbHealers > 1)
    {
        Team *t = new Team();
        t->addMonster(tankers[0]);
        t->addMonster(tankers[1]);
        t->addMonster(damages[0]);
        t->addMonster(healers[0]);

        /******** EQUIP ARMORS *******/

        if (tankers[0]->getArmor()->getId() == -1 && nbArmors > 0)
        {
            cout << "Equip armor " << armors[0]->getName() << endl;
            tankers[0]->equipArmor(armors[0]);
            armors.erase(armors.begin());
            nbArmors--;
        }

        if (tankers[1]->getArmor()->getId() == -1 && nbArmors > 0)
        {
            tankers[1]->equipArmor(armors[0]);
            armors.erase(armors.begin());
            nbArmors--;
        }

        if (damages[0]->getArmor()->getId() == -1 && nbArmors > 0)
        {
            damages[0]->equipArmor(armors[0]);
            armors.erase(armors.begin());
            nbArmors--;
        }

        if (healers[0]->getArmor()->getId() == -1 && nbArmors > 0)
        {
            healers[0]->equipArmor(armors[0]);
            armors.erase(armors.begin());
            nbArmors--;
        }

        /******** EQUIP WEAPONS *******/

        if (tankers[0]->getWeapon()->getId() == -1 && nbWeapons > 0)
        {
            tankers[0]->equipWeapon(weapons[0]);
            weapons.erase(weapons.begin());
            nbWeapons--;
        }

        if (tankers[1]->getWeapon()->getId() == -1 && nbWeapons > 0)
        {
            tankers[1]->equipWeapon(weapons[0]);
            weapons.erase(weapons.begin());
            nbWeapons--;
        }

        if (damages[0]->getWeapon()->getId() == -1 && nbWeapons > 0)
        {
            damages[0]->equipWeapon(weapons[0]);
            weapons.erase(weapons.begin());
            nbWeapons--;
        }

        if (healers[0]->getWeapon()->getId() == -1 && nbWeapons > 0)
        {
            healers[0]->equipWeapon(weapons[0]);
            weapons.erase(weapons.begin());
            nbWeapons--;
        }

        /******** EQUIP RING 1 *******/

        if (tankers[0]->getRing1()->getId() == -1 && nbRings > 0)
        {
            tankers[0]->equipRing1(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        if (tankers[1]->getRing1()->getId() == -1 && nbRings > 0)
        {
            tankers[1]->equipRing1(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        if (damages[0]->getRing1()->getId() == -1 && nbRings > 0)
        {
            damages[0]->equipRing1(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        if (healers[0]->getRing1()->getId() == -1 && nbRings > 0)
        {
            healers[0]->equipRing1(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        /******** EQUIP RING 2 ******/

        if (tankers[0]->getRing2()->getId() == -1 && nbRings > 0)
        {
            tankers[0]->equipRing2(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        if (tankers[1]->getRing2()->getId() == -1 && nbRings > 0)
        {
            tankers[1]->equipRing2(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        if (damages[0]->getRing2()->getId() == -1 && nbRings > 0)
        {
            damages[0]->equipRing2(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        if (healers[0]->getRing2()->getId() == -1 && nbRings > 0)
        {
            healers[0]->equipRing2(rings[0]);
            rings.erase(rings.begin());
            nbRings--;
        }

        /******** EQUIP TALISMANS *******/

        if (tankers[0]->getTalisman()->getId() == -1 && nbTalismans > 0)
        {
            tankers[0]->equipTalisman(talismans[0]);
            talismans.erase(talismans.begin());
            nbTalismans--;
        }

        if (tankers[1]->getTalisman()->getId() == -1 && nbTalismans > 0)
        {
            tankers[1]->equipTalisman(talismans[0]);
            talismans.erase(talismans.begin());
            nbTalismans--;
        }

        if (damages[0]->getTalisman()->getId() == -1 && nbTalismans > 0)
        {
            damages[0]->equipTalisman(talismans[0]);
            talismans.erase(talismans.begin());
            nbTalismans--;
        }

        if (healers[0]->getTalisman()->getId() == -1 && nbTalismans > 0)
        {
            healers[0]->equipTalisman(talismans[0]);
            talismans.erase(talismans.begin());
            nbTalismans--;
        }

        tankers.erase(tankers.begin());
        tankers.erase(tankers.begin());
        damages.erase(damages.begin());
        healers.erase(healers.begin());
        nbTankers -= 2;
        nbDamages--;
        nbHealers--;

        _teams.push_back(t);
        nbTeams++;
    }

    return nbTeams;
}

void Player::saveState()
{
    using json = nlohmann::json;

    ofstream playerFile("save/player.json");
    json jPlayer =
        {
            {"name", _name},
            {"monsters", _monsters.size()},
            {"items", _items.size()}};

    playerFile << jPlayer.dump(4);
    playerFile.close();

    ofstream monstersFile("save/monsters.json");
    json jMonsters;
    for (int i = 0; i < _monsters.size(); i++)
    {
        Monster *m = _monsters[i];
        json jMonster;
        jMonster["b_atk"] = m->getBaseAttack();
        jMonster["b_maxHp"] = m->getBaseMaxHp();
        jMonster["b_speed"] = m->getBaseSpeed();
        jMonster["maxStamina"] = m->getMaxStamina();
        jMonster["stamina"] = m->getMaxStamina();
        jMonster["g_atk"] = m->getAttackGrowth();
        jMonster["g_maxHp"] = m->getMaxHpGrowth();
        jMonster["g_speed"] = m->getSpeedGrowth();
        jMonster["name"] = m->getName();
        jMonster["rarity"] = m->getRarity();
        jMonster["type"] = m->getType();
        jMonster["xp"] = m->getXp();
        // jMonster["armor"] = m->getArmor()->getId();
        // jMonster["weapon"] = m->getWeapon()->getId();
        // jMonster["ring1"] = m->getRing1()->getId();
        // jMonster["ring2"] = m->getRing2()->getId();
        // jMonster["talisman"] = m->getTalisman()->getId();

        jMonsters[i] = jMonster;
    }

    monstersFile << jMonsters.dump(4);
    monstersFile.close();

    ofstream itemsFile("save/items.json");
    json jItems;
    for (int i = 0; i < _items.size(); i++)
    {
        Item *it = _items[i];
        jItems[i]["name"] = it->getName();
        jItems[i]["type"] = it->getType();
        jItems[i]["rarity"] = it->getRarity();
        jItems[i]["crit_rate"] = it->getCrit();
        jItems[i]["dodge_rate"] = it->getDodge();
        jItems[i]["combo_rate"] = it->getCombo();
        jItems[i]["stun_rate"] = it->getStun();
        jItems[i]["def_rating"] = it->getDef();
        jItems[i]["id"] = it->getId();
    }

    itemsFile << jItems.dump(4);
    itemsFile.close();
}

void Player::loadState()
{
    using json = nlohmann::json;
}

void Player::summonMonsters(int count)
{
    vector<Monster *> monsters = _game->summonMonsters(count);
    for (int i = 0; i < count; i++)
    {
        addMonster(monsters[i]);
    }
}

void Player::obtainItems(int count)
{
    vector<Item *> items = _game->obtainItems(count);
    for (int i = 0; i < count; i++)
    {
        addItem(items[i]);
    }
}

void Player::setGame(Game *g)
{
    _game = g;
}

Player::~Player()
{
    for (int i = 0; i < _teams.size(); i++)
    {
        delete _teams[i];
    }
}
