#include "Monster.hpp"
#include <string>

using namespace std;

Monster::Monster()
{
    _atk = 1000;
    _hp = 10000;
    _maxHp = 10000;
    _speed = 100;
    _maxStamina = 1000;
    _stamina = 0;

    _name = "Frog";
    _rarity = 1;

    _armor = new Item();
    _weapon = new Item();
    _ring1 = new Item();
    _ring2 = new Item();
    _talisman = new Item();
}

Monster::Monster(double atk, double mh, double speed, double ms, double s, string n, int r)
    : _atk(atk), _maxHp(mh), _speed(speed), _maxStamina(ms), _stamina(s), _name(n), _rarity(r)
{
    _hp = _maxHp;

    _armor = new Item();
    _weapon = new Item();
    _ring1 = new Item();
    _ring2 = new Item();
    _talisman = new Item();
}

void Monster::attack(Monster *target, double bonusStam)
{
    target->receiveDamage(_atk);
    _stamina = bonusStam;
}

void Monster::prepare(double modifier)
{
    _stamina += _speed * modifier;
}

void Monster::receiveDamage(double d)
{
    double damage = d * getDefenseRate();
    _hp -= damage;
}

bool Monster::isAlive() const
{
    return _hp >= 0;
}

bool Monster::canPlay() const
{
    return _stamina > _maxStamina;
}

void Monster::equipArmor(Item *a)
{
    delete _armor;
    _armor = a;
}

void Monster::equipWeapon(Item *w)
{
    delete _weapon;
    _weapon = w;
}

void Monster::equipRing1(Item *r)
{
    delete _ring1;
    _ring1 = r;
}

void Monster::equipRing2(Item *r)
{
    delete _ring2;
    _ring2 = r;
}

void Monster::equipTalisman(Item *t)
{
    delete _talisman;
    _talisman = t;
}

double Monster::getCritRate() const
{
    // TODO
    return 0;
}

double Monster::getDodgeRate() const
{
    // TODO
    return 0;
}

double Monster::getComboRate() const
{
    // TODO
    return 0;
}

double Monster::getStunRate() const
{
    // TODO
    return 0;
}

double Monster::getDefenseRate() const
{
    // TODO
    return .1;
}

double Monster::getHp() const
{
    return _hp;
}

double Monster::getMaxHp() const
{
    return _maxHp;
}

double Monster::getAttack() const
{
    return _atk;
}

double Monster::getMaxStamina() const
{
    return _maxStamina;
}

double Monster::getStamina() const
{
    return _stamina;
}

double Monster::getSpeed() const
{
    return _speed;
}

string Monster::getName() const
{
    return _name;
}

string Monster::getRarity() const
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
}

Monster::~Monster()
{
}