#pragma once

#include <string>

enum class BinaryOpType
{
    Mul,
    Div,
    Mod,
    Add,
    Sub,
    Index,
    LT,
    LEQ,
    GT,
    GEQ,
    EQ,
    NEQ,
    And,
    Or,
    Ass,
    MulAss,
    DivAss,
    AddAss,
    SubAss
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
    case BinaryOpType::LT:
        return "<";
    case BinaryOpType::LEQ:
        return "<=";
    case BinaryOpType::GT:
        return ">";
    case BinaryOpType::GEQ:
        return ">=";
    case BinaryOpType::EQ:
        return "==";
    case BinaryOpType::NEQ:
        return "!=";
    case BinaryOpType::And:
        return "and";
    case BinaryOpType::Or:
        return "or";
    case BinaryOpType::Ass:
        return "=";
    case BinaryOpType::MulAss:
        return "*=";
    case BinaryOpType::DivAss:
        return "/=";
    case BinaryOpType::AddAss:
        return "+=";
    case BinaryOpType::SubAss:
        return "-=";
    }

    // shouldnt reach here ever
    return "error";
}