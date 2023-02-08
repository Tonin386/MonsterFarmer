#include "Monster.hpp"
#include <iostream>

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

    _team = 0;
    _id = -1;
}

Monster::Monster(int id, double atk, double maxHp, double speed, double maxStamina, double stamina, string name, int rarity)
    : _id(id), _atk(atk), _maxHp(maxHp), _speed(speed), _maxStamina(maxStamina), _stamina(stamina), _name(name), _rarity(rarity)
{
    _hp = _maxHp;

    _armor = new Item();
    _weapon = new Item();
    _ring1 = new Item();
    _ring2 = new Item();
    _talisman = new Item();

    _team = 0;
}

double Monster::attack(Monster *target, double bonusStam)
{
    _stamina -= _maxStamina;
    _stamina += bonusStam;
    return target->receiveDamage(_atk);
}

void Monster::prepare(double modifier)
{
    _stamina += _speed * modifier;
}

double Monster::receiveDamage(double damage)
{
    double dealt = damage * (1 - getDefenseRate());
    _hp -= dealt;
    if(_hp <= 0) _stamina = -1;
    return dealt;
}

bool Monster::isAlive() const
{
    return _hp >= 0;
}

bool Monster::canPlay() const
{
    return _stamina >= _maxStamina;
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

    return "Error";
}

int Monster::getTeam() const
{
    return _team;
}

int Monster::getId() const
{
    return _id;
}

void Monster::setTeam(int t)
{
    _team = t;
}

bool Monster::operator==(Monster const &m) const
{
    return _name == m.getName();
}

bool Monster::operator<(Monster const &m) const
{
    // cout << "Comparing " << _stamina << " < " << m.getStamina() << " Return: " << (_stamina < m.getStamina()) << endl; 
    return _stamina < m.getStamina();
}

bool Monster::operator>(Monster const &m) const
{
    // cout << "Comparing " << _stamina << " > " << m.getStamina() << " Return: " << (_stamina > m.getStamina()) << endl; 
    return _stamina > m.getStamina();
}

void Monster::operator=(Monster const &m)
{
    _atk = m.getAttack();
    _hp = m.getHp();
    _maxHp = m.getMaxHp();
    _speed = m.getSpeed();
    _maxStamina = m.getMaxStamina();
    _stamina = m.getStamina();
    _name = m.getName();
    _rarity = m._rarity;
    //TODO add items overriding.
}

void Monster::operator=(Monster* const &m)
{
    _atk = m->getAttack();
    _hp = m->getHp();
    _maxHp = m->getMaxHp();
    _speed = m->getSpeed();
    _maxStamina = m->getMaxStamina();
    _stamina = m->getStamina();
    _name = m->getName();
    _rarity = m->_rarity;
    //TODO add items overriding.
}

Monster::~Monster()
{
}