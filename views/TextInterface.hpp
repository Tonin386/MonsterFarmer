#ifndef TEXTINTERFACE_HPP
#define TEXTINTERFACE_HPP

#include <string>

class Monster;
class Fight;
class Player;
class Team;

class TextInterface
{
protected:
    /* data */
public:
    TextInterface();

    static void log(std::string s);
    static void log(Monster *m);
    static void log(Fight *f);
    static void log(Player *p);
    static void log(Team *t);

    ~TextInterface();
};

#endif