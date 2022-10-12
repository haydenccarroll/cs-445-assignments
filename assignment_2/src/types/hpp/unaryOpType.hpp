#pragma once

#include <string>

enum class UnaryOpType
{
    Chsign,
    SizeOf,
    Question,
    Not
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
    }

    // shouldnt reach here ever
    return "error";
}
