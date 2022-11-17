#pragma once

#include <string>

// to pass data between l file and y file
struct TokenData
{
    std::string str;      // used for identifiers, the string value of a number, etc.
    std::string inputStr; // used for when keeping track of the input string of something
    char charV;           // used for characters
    int num;              // used for numbers
    bool boolV;
    int lineNum; // line where token found
};