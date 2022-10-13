#pragma once

#include <string>

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

inline std::string assignOpTypeToStr(AssignOpType type)
{
    switch(type)
    {
    case AssignOpType::ASS:
        return "=";
    case AssignOpType::MULASS:
        return "*=";
    case AssignOpType::DIVASS:
        return "/=";
    case AssignOpType::ADDASS:
        return "+=";
    case AssignOpType::SUBASS:
        return "-=";
    case AssignOpType::INC:
        return "++";
    case AssignOpType::DEC:
        return "--";
    }

    // shouldnt reach here ever
    return "error";
}