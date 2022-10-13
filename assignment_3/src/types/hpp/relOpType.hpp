#pragma once

#include <string>

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