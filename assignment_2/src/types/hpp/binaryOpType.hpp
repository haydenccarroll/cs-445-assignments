#pragma once

#include <string>

enum class BinaryOpType
{
    Mul,
    Div,
    Mod,
    Add,
    Sub,
    Index
};

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