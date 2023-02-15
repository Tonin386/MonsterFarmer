#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item
{
protected:
    double _crit;
    double _dodge;
    double _combo;
    double _stun;
    double _def;
    std::string _name;
    char _type;
    double _rating;
    int _rarity;
    int _id;

public:
    Item();
    Item(double crit, double dodge, double combo, double stun, double def, std::string name, char type, int rarity);
    Item(Item *i);

    virtual double getCrit() const;
    virtual double getDodge() const;
    virtual double getCombo() const;
    virtual double getStun() const;
    virtual double getDef() const;
    virtual std::string getName() const;
    virtual char getType() const;
    virtual std::string getVerboseType() const;
    virtual double getRating() const;
    virtual int getRarity() const;
    virtual std::string getVerboseRarity() const;
    virtual int getId() const;

    virtual void setId(int id);

    static const char ARMOR_TYPE = 'A';
    static const char WEAPON_TYPE = 'W';
    static const char RING_TYPE = 'R';
    static const char TALISMAN_TYPE = 'T';

    ~Item();
};

#endif