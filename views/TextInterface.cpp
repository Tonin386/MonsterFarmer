#include "TextInterface.hpp"

#include "../game/entities/monsters/Monster.hpp"
#include "../game/entities/monsters/Team.hpp"
#include "../game/entities/players/Player.hpp"
#include "../game/scenarios/Fight.hpp"
#include "../game/entities/items/Item.hpp"

#include <iostream>
#include <iomanip>
#include <map>
#include <cstdlib>
#include <unistd.h>
#include <stdlib.h>

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

    if (f->hasEnded())
    {
        if (attackers->hasLost())
            cout << "LOSE" << endl;
        else
            cout << "WIN" << endl;
    }

    cout << fixed;
    cout << setprecision(2);

    cout << "Attackers (" << f->getAttackersRating() << ") vs Defenders(" << f->getDefendersRating() << ")" << endl;

    for (int i = 0; i < 8; i++)
    {
        int id = all[i]->getId();
        cout << all[i]->getName() << " attacked " << attacksCount[id] << " times for a total of " << damageDealt[id] << " of damage done." << endl;
    }
}

void TextInterface::log(Monster *m)
{
    cout << fixed;
    cout << setprecision(2);
    cout << m->getName() << "[" << m->getId() << "]" << endl;
    cout << "+ Rarity: " << m->getVerboseRarity() << endl;
    cout << "+ Class: " << m->getVerboseType() << endl;
    cout << "+ Overall rating: " << m->getRating() << endl;
    cout << "+ Attack value: " << m->getAttack() << endl;
    cout << "+ Health points: " << m->getHp() << "/" << m->getMaxHp() << endl;
    cout << "+ Speed: " << m->getSpeed() << endl;
    cout << "+ Stamina: " << m->getStamina() << "/" << m->getMaxStamina() << endl;
    cout << "+ Level: " << m->getLevel() << endl;
    log(m->getArmor());
    log(m->getWeapon());
    log(m->getRing1());
    log(m->getRing2());
    log(m->getTalisman());
    cout << "--------------------------" << endl;
}

void TextInterface::log(Item *m)
{
    if (m->getType() != '?')
    {
        cout << fixed;
        cout << setprecision(2);
        cout << "\t" << m->getName() << "[" << m->getId() << "]" << endl;
        cout << "\t+ Rarity: " << m->getVerboseRarity() << endl;
        cout << "\t+ Type: " << m->getVerboseType() << endl;
        cout << "\t+ Overall rating: " << m->getRating() << endl;
        cout << "\t+ Critical rate: " << m->getCrit() << endl;
        cout << "\t+ Dodge rate: " << m->getDodge() << endl;
        cout << "\t+ Combo rate: " << m->getCombo() << endl;
        cout << "\t+ Stun rate: " << m->getStun() << endl;
        cout << "\t+ Defense rating: " << m->getDef() << endl;
        cout << "\t*********************" << endl;
    }
    else
    {
        cout << "\tNo item" << endl;
    }
}

void TextInterface::log(Player *p)
{
    vector<Team *> teams = p->getTeams();
    cout << "List of teams (" << teams.size() << ") of " << p->getName() << endl;
    for (int i = 0; i < teams.size(); i++)
    {
        cout << "Team " << i+1 << "/" << teams.size() << endl;
        log(teams[i]);
    }
}

void TextInterface::log(Team *t)
{
    cout << "--------------- Beginning of team -----------------" << endl;

    cout << "Average rating: " << t->getAverageRating() << endl;
    for (int i = 0; i < 4; i++)
    {
        log((*t)[i]);
    }

    cout << "----------------- End of team -----------------" << endl;
}

void TextInterface::clear(double seconds)
{
    usleep(1000000 * seconds);
    system("cls");
}

TextInterface::~TextInterface()
{
}
