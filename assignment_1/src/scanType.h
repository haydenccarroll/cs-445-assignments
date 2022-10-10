#pragma once

#include <string>

enum TokenClass
{

};

struct TokenData
{
    std::string str;      // used for identifiers, the string value of a number, etc.
    std::string inputStr; // used for when keeping track of the input string of something
    char charV;           // used for characters
    int num;              // used for numbers as well as bools (0 false 1 true)
    unsigned int lineNum; // line where token found
};

