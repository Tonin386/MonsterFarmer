#include "Monster.hpp"

#include "../../../views/TextInterface.hpp"
#include "../items/Item.hpp"

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
    _type = 0;

    _armor = new Item();
    _weapon = new Item();
    _ring1 = new Item();
    _ring2 = new Item();
    _talisman = new Item();

    _team = 0;
    _id = -1;

    _level = 0;
    _xp = 0;
    _stunned = false;
}

Monster::Monster(string name, int rarity, int type, double baseAtk, double baseMaxHp, double baseSpeed, double atkGrowth, double maxHpGrowth, double speedGrowth, double maxStamina, double stamina, double xp)
    : b_atk(baseAtk), b_maxHp(baseMaxHp), b_speed(baseSpeed), _maxStamina(maxStamina), _stamina(stamina), _name(name), _rarity(rarity), _type(type), g_atk(atkGrowth), g_maxHp(maxHpGrowth), g_speed(speedGrowth)
{
    _atk = b_atk;
    _maxHp = b_maxHp;
    _speed = b_speed;
    _hp = _maxHp;

    _level = 0;
    levelUp(xp);

    _armor = new Item();
    _weapon = new Item();
    _ring1 = new Item();
    _ring2 = new Item();
    _talisman = new Item();

    _team = 0;
    _id = -1;
    _stunned = false;
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
    _type = m->_type;

    _armor = m->_armor;
    _weapon = m->_weapon;
    _ring1 = m->_ring1;
    _ring2 = m->_ring2;
    _talisman = m->_talisman;

    _team = m->_team;

    _xp = m->_xp;
    _level = m->_level;
    _id = -1;
    _stunned = false;
}

double Monster::attack(Monster *target, double bonusStam)
{
    _stamina -= _maxStamina;
    _stamina += bonusStam;

    if (rand() % 10001 < getCritRate() * 100)
        return target->receiveDamage(_atk * 2);

    return target->receiveDamage(_atk);
}

void Monster::prepare(double modifier)
{
    _stamina += _speed * modifier;
    _stunned = false;
}

double Monster::receiveDamage(double damage)
{
    if (rand() % 10001 < getDodgeRate() * 100)
        return 0;
    double dealt = damage * (1 - getDefenseRate());
    _hp -= dealt;
    if (_hp <= 0)
        _stamina = -1;
    return dealt;
}

void Monster::stun()
{
    _stunned = true;
}

bool Monster::isAlive() const
{
    return _hp >= 0;
}

bool Monster::isStunned() const
{
    return _stunned;
}

bool Monster::canPlay() const
{
    return _stamina >= _maxStamina;
}

int Monster::levelUp(double xp)
{
    _xp += xp;
    int newLevel = floor((sqrt(625 + 100 * _xp) - 25) / 50);
    if (newLevel > _level)
    {
        _atk = b_atk * (1 + g_atk * newLevel);
        _maxHp = b_maxHp * (1 + g_maxHp * newLevel);
        _speed = b_speed * (1 + g_speed * newLevel);
    }

    _level = newLevel;

    return newLevel;
}

void Monster::reset(bool levelReset)
{
    _hp = _maxHp;
    _stamina = 0;
    desequipArmor();
}

void Monster::equipArmor(Item *a)
{
    _armor = a;
}

void Monster::equipWeapon(Item *w)
{
    _weapon = w;
}

void Monster::equipRing1(Item *r)
{
    _ring1 = r;
}

void Monster::equipRing2(Item *r)
{
    _ring2 = r;
}

void Monster::equipTalisman(Item *t)
{
    _talisman = t;
}

void Monster::desequipArmor()
{
    _armor = new Item();
    _weapon = new Item();
    _ring1 = new Item();
    _ring2 = new Item();
    _talisman = new Item();
}

Item *Monster::getArmor() const
{
    return _armor;
}

Item *Monster::getWeapon() const
{
    return _weapon;
}

Item *Monster::getRing1() const
{
    return _ring1;
}

Item *Monster::getRing2() const
{
    return _ring2;
}

Item *Monster::getTalisman() const
{
    return _talisman;
}

double Monster::getCritRate() const
{
    return _armor->getCrit() + _weapon->getCrit() + _ring1->getCrit() + _ring2->getCrit() + _talisman->getCrit();
}

double Monster::getDodgeRate() const
{
    return _armor->getDodge() + _weapon->getDodge() + _ring1->getDodge() + _ring2->getDodge() + _talisman->getDodge();
}

double Monster::getComboRate() const
{
    return _armor->getCombo() + _weapon->getCombo() + _ring1->getCombo() + _ring2->getCombo() + _talisman->getCombo();
}

double Monster::getStunRate() const
{
    return _armor->getStun() + _weapon->getStun() + _ring1->getStun() + _ring2->getStun() + _talisman->getStun();
}

double Monster::getDefenseRate() const
{
    return (1 - (10000 / (10000 + _armor->getDef() + _weapon->getDef() + _ring1->getDef() + _ring2->getDef() + _talisman->getDef())));
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

int Monster::getType() const
{
    return _type;
}

string Monster::getVerboseType() const
{
    switch (_type)
    {
    case TANKER:
        return "Tanker";
    case DAMAGE:
        return "Damage";
    case HEALER:
        return "Healer";
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

double Monster::getRating() const
{
    return (_atk + _maxHp / 100 + _speed * 10) / 30;
}

double Monster::getItemsRating()
{
    return _armor->getRating() + _weapon->getRating() + _ring1->getRating() + _ring2->getRating() + _talisman->getRating();
}

double Monster::getXp() const
{
    return _xp;
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
    return _stamina < m.getStamina();
}

bool Monster::operator>(Monster const &m) const
{
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
    _armor = m.getArmor();
    _weapon = m.getWeapon();
    _ring1 = m.getRing1();
    _ring2 = m.getRing2();
    _talisman = m.getTalisman();
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
    _armor = m->getArmor();
    _weapon = m->getWeapon();
    _ring1 = m->getRing1();
    _ring2 = m->getRing2();
    _talisman = m->getTalisman();
}

double Monster::xpForLevel(int level)
{
    return 25 * level * level + 25 * level;
}

Monster::~Monster()
{
}