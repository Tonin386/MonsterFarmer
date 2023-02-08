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

    virtual void log(std::string s) const;

    ~TextInterface();
};

#endif