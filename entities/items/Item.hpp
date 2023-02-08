#ifndef ITEM_HPP
#define ITEM_HPP

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

public:
    Item();
    Item(double crit, double dodge, double combo, double stun, double def, std::string name, char type, int rarity);

    virtual double          getCrit()   const;
    virtual double          getDodge()  const;
    virtual double          getCombo()  const;
    virtual double          getStun()   const;
    virtual double          getDef()    const;
    virtual std::string     getName()   const;
    virtual char            getType()   const;
    virtual double          getRating() const;
    virtual std::string     getRarity() const;

    ~Item();
};


#endif