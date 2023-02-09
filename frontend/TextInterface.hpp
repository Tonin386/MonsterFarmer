#ifndef TEXTINTERFACE_HPP
#define TEXTINTERFACE_HPP

class Monster;
class Fight;

#include <string>

class TextInterface
{
protected:
    /* data */
public:
    TextInterface();

    static void log(std::string s);
    static void showStats(Monster *m);
    static void showStats(Fight *f);

    ~TextInterface();
};

#endif