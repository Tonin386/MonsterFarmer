#include "Monster.hpp"

#include "../frontend/TextInterface.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Monster::Monster()
{
    b_atk = 1000;
    b_maxHp = 10000;
    b_speed = 100;

    _atk = b_atk;
    _maxHp = b_maxHp;
    _speed = b_speed;
    _hp = _maxHp;
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
    _rating = (_atk + _maxHp/10 + _speed*10) / 30;

    _level = 0;
    _xp = 0;
}

Monster::Monster(string name, int rarity, double baseAtk, double baseMaxHp, double baseSpeed, double atkGrowth, double maxHpGrowth, double speedGrowth, double maxStamina, double stamina, double xp)
    : b_atk(baseAtk), b_maxHp(baseMaxHp), b_speed(baseSpeed), _maxStamina(maxStamina), _stamina(stamina), _name(name), _rarity(rarity), _xp(xp)
{
    _atk = b_atk;
    _maxHp = b_maxHp;
    _speed = b_speed;
    _hp = _maxHp;

    _level = 0;
    levelUp(false);

    _armor = new Item();
    _weapon = new Item();
    _ring1 = new Item();
    _ring2 = new Item();
    _talisman = new Item();

    _team = 0;
    _id = -1;
    _rating = (_atk + _maxHp/10 + _speed*10) / 30;
}

Monster::Monster(Monster *m)
{
    _atk = m->_atk;
    _hp = m->_hp;
    _maxHp = m->_maxHp;
    _speed = m->_speed;
    _maxStamina = m->_maxStamina;
    _stamina = m->_stamina;

    g_atk = m->g_atk;
    g_maxHp = m->g_maxHp;
    g_speed = m->g_speed;
    
    b_atk = m->b_atk;
    b_maxHp = m->b_maxHp;
    b_speed = m->b_speed;

    _name = m->_name;
    _rarity = m->_rarity;

    _armor = m->_armor;
    _weapon = m->_weapon;
    _ring1 = m->_ring1;
    _ring2 = m->_ring2;
    _talisman = m->_talisman;

    _team = m->_team;
    _rating = m->_rating;

    _xp = m->_xp;
    _level = m->_level;
    _id = -1;
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
    if (_hp <= 0)
        _stamina = -1;
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

double Monster::calcTotalXpForLevel(int level)
{
    return level^2 * 1000;
}

int Monster::levelUp(bool verbose)
{  
    int i = 0;

    while(calcTotalXpForLevel(i + _level) < _xp) {i++;}
    if(i >= 1)
    {
        _level += i;
        _atk = b_atk * (1 + _level * g_atk);
        _maxHp = b_maxHp * (1 + _level * g_maxHp);
        _speed = b_speed * (1 + _level * g_speed);
        
        if(verbose)
        {
            TextInterface::log(_name + " gained " + to_string(i) + " level(s) and now is level " + to_string(_level));
        }
    }

    return i;
}

void Monster::addXp(double xp)
{
    _xp += xp;
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

double Monster::getBaseAttack() const
{
    return b_atk;
}

double Monster::getBaseMaxHp() const
{
    return b_maxHp;
}

double Monster::getBaseSpeed() const
{
    return b_speed;
}

double Monster::getAttackGrowth() const
{
    return g_atk;
}

double Monster::getMaxHpGrowth() const
{
    return g_maxHp;
}

double Monster::getSpeedGrowth() const
{
    return g_speed;
}

string Monster::getName() const
{
    return _name;
}

string Monster::getVerboseRarity() const
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

int Monster::getRarity() const
{
    return _rarity;
}

int Monster::getTeam() const
{
    return _team;
}

int Monster::getId() const
{
    return _id;
}

double Monster::getRating() const
{
    return _rating;
}

int Monster::getLevel() const
{
    return _level;
}

void Monster::setTeam(int t)
{
    _team = t;
}

void Monster::setId(int id)
{
    _id = id;
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
    // TODO add items overriding.
}

void Monster::operator=(Monster *const &m)
{
    _atk = m->getAttack();
    _hp = m->getHp();
    _maxHp = m->getMaxHp();
    _speed = m->getSpeed();
    _maxStamina = m->getMaxStamina();
    _stamina = m->getStamina();
    _name = m->getName();
    _rarity = m->_rarity;
    // TODO add items overriding.
}

Monster::~Monster()
{
}