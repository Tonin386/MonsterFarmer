#include "Item.hpp"

using namespace std;

Item::Item()
{
    // The sum of crit, dodge, combo and stun cannot be > 100 for Legendary item
    _crit = 1;
    _dodge = 1;
    _combo = 1;
    _stun = 1;
    _def = 1000; // Max defense should be 100000. equivalent to 100% def.
    _name = "Unwearable item";
    _type = '?';

    _rating = ((_crit + _dodge + _combo + _stun) * 10 + _def / 100) / 20;
    _rarity = 1;
}

Item::Item(double crit, double dodge, double combo, double stun, double def, string name, char type, int rarity)
    : _crit(crit), _dodge(dodge), _combo(combo), _stun(stun), _def(def), _name(name), _type(type), _rarity(rarity)
{
    // Well it's done actually...
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

double Item::getRating() const
{
    return _rating;
}

string Item::getRarity() const
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

Item::~Item()
{
}
