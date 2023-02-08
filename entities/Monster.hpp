#ifndef MONSTER_HPP
#define MONSTER8HPP

class Monster
{
protected:
    int _atk;
    int _hp;
    int _maxhp;

public:
    Monster();
    Monster(int a, int h, int mh);

    virtual void attack(Monster *target);

    virtual bool isAlive() const;

    virtual int getHp() const;
    virtual int getMaxHp() const;

    ~Monster();
};

#endif 