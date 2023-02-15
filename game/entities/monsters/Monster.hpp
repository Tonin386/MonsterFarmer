#ifndef MONSTER_HPP
#define MONSTER8HPP

#include <string>

class Item;

class Monster
{
protected:
    double _atk;
    double _hp;
    double _maxHp;
    double _speed;
    double _maxStamina;
    double _stamina;

    double g_atk;
    double g_maxHp;
    double g_speed;
    
    double b_atk;
    double b_maxHp;
    double b_speed;

    std::string _name;
    int _rarity;
    int _type;

    Item *_armor;
    Item *_weapon;
    Item *_ring1;
    Item *_ring2;
    Item *_talisman;

    int _team;
    int _id;

    double _xp;
    int _level;

public:
    Monster();
    Monster(
        std::string name,
        int rarity,
        int type,
        double baseAtk,
        double baseMaxHp,
        double baseSpeed,
        double atkGrowth,
        double maxHpGrowth,
        double speedGrowth,
        double maxStamina,
        double stamina,
        double xp);

    Monster(Monster *m);

    /* TURN RELATED FUNCTIONS */
    virtual double attack(Monster *target, double bonusStam = 0);
    virtual void prepare(double modifier = 1);
    virtual double receiveDamage(double damage);

    virtual bool isAlive() const;
    virtual bool canPlay() const;

    /* MANAGE MONSTER FUNCTIONS */
    virtual int levelUp(double xp);
    virtual void reset(bool levelReset = false);

    /* STUFF RELATED FUNCTIONS */
    virtual void equipArmor(Item *a);
    virtual void equipWeapon(Item *w);
    virtual void equipRing1(Item *r);
    virtual void equipRing2(Item *r);
    virtual void equipTalisman(Item *t);

    virtual Item* getArmor() const;
    virtual Item* getWeapon() const;
    virtual Item* getRing1() const;
    virtual Item* getRing2() const;
    virtual Item* getTalisman() const;

    /* DAMAGE DONE MODIFIERS */
    virtual double getCritRate() const;
    virtual double getDodgeRate() const;
    virtual double getComboRate() const;
    virtual double getStunRate() const;

    /* INCOMING DAMAGE MODIFIERS */
    virtual double getDefenseRate() const;

    /* SETTERS & GETTERS OF ATTRIBUTES */
    virtual double getHp() const;
    virtual double getMaxHp() const;
    virtual double getAttack() const;
    virtual double getMaxStamina() const;
    virtual double getStamina() const;
    virtual double getSpeed() const;
    virtual double getBaseAttack() const;
    virtual double getBaseMaxHp() const;
    virtual double getBaseSpeed() const;
    virtual double getAttackGrowth() const;
    virtual double getMaxHpGrowth() const;
    virtual double getSpeedGrowth() const;
    virtual std::string getName() const;
    virtual int getRarity() const;
    virtual std::string getVerboseRarity() const;
    virtual int getType() const;
    virtual std::string getVerboseType() const;
    virtual int getTeam() const;
    virtual int getId() const;
    virtual double getRating() const;
    virtual double getXp() const;
    virtual int getLevel() const;

    virtual void setTeam(int t);
    virtual void setId(int id);

    /* OPERATORS */
    virtual bool operator==(Monster const &m) const;
    virtual bool operator<(Monster const &m) const;
    virtual bool operator>(Monster const &m) const;
    virtual void operator=(Monster const &m);
    virtual void operator=(Monster *const &m);

    static const int TANKER = 0;
    static const int DAMAGE = 1;
    static const int HEALER = 2;

    ~Monster();
};

#endif