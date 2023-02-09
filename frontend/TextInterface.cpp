#include "TextInterface.hpp"

#include "../gameMethods/Fight.hpp"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;

TextInterface::TextInterface() {}

void TextInterface::log(string s)
{
    cout << s << endl;
}

void TextInterface::showStats(Fight *f)
{
    vector<Monster*> all = f->getMonsters();
    Team* attackers = f->getAttackers();
    Team* defenders = f->getDefenders();
    map<int, int> attacksCount = f->getAttacksCount();
    map<int, double> damageDealt = f->getDamageDealt();
    
    cout << fixed;
    cout << setprecision(2);

    for (int i = 0; i < 8; i++)
    {
        int id = all[i]->getId();
        cout << all[i]->getName() << " attacked " << attacksCount[id] << " times for a total of " << damageDealt[id] << " of damage done." << endl;
    }
}

void TextInterface::showStats(Monster* m)
{
    cout << fixed;
    cout << setprecision(2);
    cout << "Stats for " << m->getName() << "[" << m->getId() << "]" << endl;
    cout << "+ Rarity: " << m->getVerboseRarity() << endl;
    cout << "+ Attack value: " << m->getAttack() << endl;
    cout << "+ Health points: " << m->getHp() << "/" << m->getMaxHp() << endl;
    cout << "+ Speed: " << m->getSpeed() << endl;
    cout << "+ Stamina: " << m->getStamina() << "/" << m->getMaxStamina() << endl;
    cout << "+ Level: " << m->getLevel() << endl;
    cout << "--------------------------" << endl;
}


TextInterface::~TextInterface()
{
}
