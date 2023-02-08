#ifndef TEXTINTERFACE_HPP
#define TEXTINTERFACE_HPP

#include <iostream>
#include <string>

class TextInterface
{
protected:
    /* data */
public:
    TextInterface();

    static void log(std::string s);

    ~TextInterface();
};

#endif