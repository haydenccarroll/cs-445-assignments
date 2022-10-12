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
    Void
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
    Sub,
    Index
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


inline std::string dataTypeToStr(DataType type)
{
    switch(type)
    {
    case DataType::Int:
        return "int";
    case DataType::Bool:
        return "bool";
    case DataType::Char:
        return "char";
    case DataType::Void:
        return "void";
    }

    // shouldnt reach here ever
    return "error";
}

inline std::string assignOpTypeToStr(AssignOpType type)
{
    switch(type)
    {
    case AssignOpType::ASS:
        return "=";
    case AssignOpType::MULASS:
        return "MUL";
    case AssignOpType::DIVASS:
        return "DIV";
    case AssignOpType::ADDASS:
        return "ADD";
    case AssignOpType::SUBASS:
        return "SUB";
    case AssignOpType::INC:
        return "++";
    case AssignOpType::DEC:
        return "--";
    }

    // shouldnt reach here ever
    return "error";
}

inline std::string binaryOpTypeToStr(BinaryOpType type)
{
    switch(type)
    {
    case BinaryOpType::Mul:
        return "*";
    case BinaryOpType::Div:
        return "/";
    case BinaryOpType::Mod:
        return "%";
    case BinaryOpType::Add:
        return "+";
    case BinaryOpType::Sub:
        return "-";
    case BinaryOpType::Index:
        return "[";
    }

    // shouldnt reach here ever
    return "error";
}

inline std::string unaryOpTypeToStr(UnaryOpType type)
{
    switch(type)
    {
    case UnaryOpType::Chsign:
        return "chsign";
    case UnaryOpType::SizeOf:
        return "sizeof";
    case UnaryOpType::Question:
        return "?";
    }

    // shouldnt reach here ever
    return "error";
}

inline std::string relOpTypeToStr(RelOpType type)
{
    switch(type)
    {
    case RelOpType::LT:
        return "<";
    case RelOpType::LEQ:
        return "<=";
    case RelOpType::GT:
        return ">";
    case RelOpType::GEQ:
        return ">=";
    case RelOpType::EQ:
        return "==";
    case RelOpType::NEQ:
        return "!=";
    case RelOpType::And:
        return "and";
    case RelOpType::Or:
        return "or";
    }

    // shouldnt reach here ever
    return "error";
}
