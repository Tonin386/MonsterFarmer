#include "TextInterface.hpp"

using namespace std;

TextInterface::TextInterface() {}

void TextInterface::log(string s) const
{
    cout << s << endl;
}

TextInterface::~TextInterface()
{
}
