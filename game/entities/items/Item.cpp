#include "Item.hpp"

#include <iostream>

using namespace std;

Item::Item()
{
    // The sum of crit, dodge, combo and stun cannot be > 100 for Legendary item
    _crit = 0;
    _dodge = 0;
    _combo = 0;
    _stun = 0;
    _def = 0; // Max defense should be 100000. equivalent to 100% def.
    _name = "Unwearable item";
    _type = '?';

        _rating = (((_crit + _dodge + _combo + _stun) * 5) * (1 - (10000 / (10000 + 4*_def))));

    _rarity = 1;
    _id = -1;
}

Item::Item(double crit, double dodge, double combo, double stun, double def, string name, char type, int rarity)
    : _crit(crit), _dodge(dodge), _combo(combo), _stun(stun), _def(def), _name(name), _type(type), _rarity(rarity)
{
    _rating = (((_crit + _dodge + _combo + _stun) * 5) * (1 - (10000 / (10000 + 4*_def))));
}

Item::Item(Item *i)
{
    _crit = i->getCrit();
    _dodge = i->getDodge();
    _combo = i->getCombo();
    _stun = i->getStun();
    _def = i->getDef();

    _name = i->getName();
    _type = i->getType();
    _rating = i->getRating();
    _rarity = i->getRarity();
    _id = -1;
}

double Item::getCrit() const
{
    return _crit;
}

double Item::getDodge() const
{
    return _dodge;
}

double Item::getCombo() const
{
    return _combo;
}

double Item::getStun() const
{
    return _stun;
}

double Item::getDef() const
{
    return _def;
}

string Item::getName() const
{
    return _name;
}

char Item::getType() const
{
    return _type;
}

string Item::getVerboseType() const
{
    switch (_type)
    {
    case ARMOR_TYPE:
        return "Armor";
    case WEAPON_TYPE:
        return "Weapon";
    case RING_TYPE:
        return "Ring";
    case TALISMAN_TYPE:
        return "Talisman";
    }

    return "Error";
}

double Item::getRating() const
{
    return _rating;
}

int Item::getRarity() const
{
    return _rarity;
}

string Item::getVerboseRarity() const
{
    switch (_rarity)
    {
    case 1:
        return "Common";
        break;
    case 2:
        return "Uncommon";
        break;
    case 3:
        return "Rare";
        break;
    case 4:
        return "Epic";
        break;
    case 5:
        return "Legendary";
        break;
    }

    return "Error";
}

int Item::getId() const
{
    return _id;
}

void Item::setId(int id)
{
    _id = id;
}

Item::~Item()
{
}
