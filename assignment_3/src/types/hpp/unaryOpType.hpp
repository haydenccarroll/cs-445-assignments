#pragma once

#include <string>

enum class UnaryOpType
{
    Chsign,
    SizeOf,
    Question,
    Not,
    Inc,
    Dec
};

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
    case UnaryOpType::Not:
        return "not";
    case UnaryOpType::Inc:
        return "++";
    case UnaryOpType::Dec:
        return "--";
    }

    // shouldnt reach here ever
    return "error";
}
