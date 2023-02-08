#ifndef MONSTER_HPP
#define MONSTER8HPP

#include "items/Item.hpp"

class Monster
{
protected:
    double _atk;
    double _hp;
    double _maxHp;
    double _speed;
    double _maxStamina;
    double _stamina;

    std::string _name;
    int _rarity;

    Item *_armor;
    Item *_weapon;
    Item *_ring1;
    Item *_ring2;
    Item *_talisman;

    int _team;
    int _id;

public:
    Monster();
    Monster(
        int id,
        double atk,
        double maxHp,
        double speed,
        double maxStamina,
        double stamina,
        std::string name,
        int rarity);

    /* TURN RELATED FUNCTIONS */
    virtual double  attack(Monster *target, double bonusStam = 0);
    virtual void    prepare(double modifier = 1);
    virtual double  receiveDamage(double damage);

    virtual bool isAlive() const;
    virtual bool canPlay() const;

    /* STUFF RELATED FUNCTIONS */
    virtual void equipArmor(Item *a);
    virtual void equipWeapon(Item *w);
    virtual void equipRing1(Item *r);
    virtual void equipRing2(Item *r);
    virtual void equipTalisman(Item *t);

    /* DAMAGE DONE MODIFIERS */
    virtual double getCritRate() const;
    virtual double getDodgeRate() const;
    virtual double getComboRate() const;
    virtual double getStunRate() const;

    /* INCOMING DAMAGE MODIFIERS */
    virtual double getDefenseRate() const;

    /* SETTERS & GETTERS OF ATTRIBUTES */
    virtual double      getHp()         const;
    virtual double      getMaxHp()      const;
    virtual double      getAttack()     const;
    virtual double      getMaxStamina() const;
    virtual double      getStamina()    const;
    virtual double      getSpeed()      const;
    virtual std::string getName()       const;
    virtual std::string getRarity()     const;
    virtual int         getTeam()       const;
    virtual int         getId()         const;

    virtual void setTeam(int t);

    /* OPERATORS */
    virtual bool operator==(Monster const &m) const;
    virtual bool operator<(Monster const &m) const;
    virtual bool operator>(Monster const &m) const;
    virtual void operator=(Monster const &m);
    virtual void operator=(Monster *const &m);

    ~Monster();
};

#endif