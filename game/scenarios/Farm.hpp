#ifndef FARM_HPP
#define FARM_HPP

#include <cstdlib>
#include <ctime>

class Farm
{
protected:
public:
    Farm();

    virtual int summonMonster();
    virtual int obtainItem();

    ~Farm();
};

#endif