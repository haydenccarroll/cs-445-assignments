#pragma once

// necessary for .l and .y files
#include "ast/node.hpp"

#include <string>

// to pass data between l file and y file
struct TokenData
{
    std::string str;      // used for identifiers, the string value of a number, etc.
    std::string inputStr; // used for when keeping track of the input string of something
    char charV;           // used for characters
    int num;              // used for numbers as well as bools (0 false 1 true)
    unsigned int lineNum; // line where token found
};

enum class DataType
{
    Int,
    Bool,
    Char,
    Void,
    None
};

enum class ConstType
{
    Int,
    Bool,
    Char,
    String
};

enum class UnaryOpType
{
    Chsign,
    SizeOf,
    Question
};

enum class BinaryOpType
{
    Mul,
    Div,
    Mod,
    Add,
    Sub
};

enum class RelOpType
{
    LT,
    LEQ,
    GT,
    GEQ,
    EQ,
    NEQ,
    And,
    Or
};

enum class AssignOpType
{
    ASS,
    MULASS,
    DIVASS,
    ADDASS,
    SUBASS,
    INC,
    DEC
};
