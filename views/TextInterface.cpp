#include "TextInterface.hpp"

#include "../game/entities/monsters/Monster.hpp"
#include "../game/entities/monsters/Team.hpp"
#include "../game/entities/players/Player.hpp"
#include "../game/scenarios/Fight.hpp"
#include "../game/entities/items/Item.hpp"

#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

TextInterface::TextInterface() {}

void TextInterface::log(string s)
{
    cout << s << endl;
}

void TextInterface::log(Fight *f)
{
    vector<Monster *> all = f->getMonsters();
    Team *attackers = f->getAttackers();
    Team *defenders = f->getDefenders();
    map<int, int> attacksCount = f->getAttacksCount();
    map<int, double> damageDealt = f->getDamageDealt();

    cout << fixed;
    cout << setprecision(2);

    for (int i = 0; i < 8; i++)
    {
        int id = all[i]->getId();
        cout << all[i]->getName() << " attacked " << attacksCount[id] << " times for a total of " << damageDealt[id] << " of damage done." << endl;
    }

    if(f->hasEnded())
    {
        if (attackers->hasLost())
            cout << "Attackers lost." << endl;
        else
            cout << "Attackers won." << endl;
    }
}

void TextInterface::log(Monster *m)
{
    cout << fixed;
    cout << setprecision(2);
    cout << "Stats for " << m->getName() << "[" << m->getId() << "]" << endl;
    cout << "+ Rarity: " << m->getVerboseRarity() << endl;
    cout << "+ Class: " << m->getVerboseType() << endl;
    cout << "+ Overall rating: " << m->getRating() << endl;
    cout << "+ Attack value: " << m->getAttack() << endl;
    cout << "+ Health points: " << m->getHp() << "/" << m->getMaxHp() << endl;
    cout << "+ Speed: " << m->getSpeed() << endl;
    cout << "+ Stamina: " << m->getStamina() << "/" << m->getMaxStamina() << endl;
    cout << "+ Level: " << m->getLevel() << endl;
    cout << "--------------------------" << endl;
}

void TextInterface::log(Item *m)
{
    cout << fixed;
    cout << setprecision(2);
    cout << "Stats for " << m->getName() << "[" << m->getId() << "]" << endl;
    cout << "+ Rarity: " << m->getVerboseRarity() << endl;
    cout << "+ Type: " << m->getVerboseType() << endl;
    cout << "+ Overall rating: " << m->getRating() << endl;
    cout << "+ Critical rate: " << m->getCrit() << endl;
    cout << "+ Dodge rate: " << m->getDodge() << endl;
    cout << "+ Combo rate: " << m->getCombo() << endl;
    cout << "+ Stun rate: " << m->getStun() << endl;
    cout << "+ Defense rating: " << m->getDef() << endl;
    cout << "--------------------------" << endl;
}

void TextInterface::log(Player *p)
{
    vector<Team *> teams = p->getTeams();
    cout << "List of teams (" << teams.size() << ") of " << p->getName() << endl;
    for (int i = 0; i < teams.size(); i++)
    {
        log(teams[i]);
    }
}

void TextInterface::log(Team *t)
{
    cout << "--------------- Beginning of team -----------------" << endl;

    for (int i = 0; i < 4; i++)
    {
        log((*t)[i]);
    }

    cout << "----------------- End of team -----------------" << endl;
}

TextInterface::~TextInterface()
{
}
