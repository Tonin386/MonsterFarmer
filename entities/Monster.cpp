#include "Monster.hpp"

Monster::Monster() {}

Monster::Monster(int a, int h, int mh) : _atk(a), _hp(h) , _maxhp(mh) {}

void Monster::attack(Monster* target)
{
    target->_hp -= _atk;
}

bool Monster::isAlive() const
{
    return _hp >= 0;
}

int Monster::getHp() const
{
    return _hp;
}

int Monster::getMaxHp() const
{
    return _maxhp;
}

Monster::~Monster()
{
}