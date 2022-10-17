#include "../../hpp/subclasses/binaryOp.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include "../../../types/types.hpp"

#include <iostream>

BinaryOpNode::BinaryOpNode(unsigned int lineNum, BinaryOpType type) : 
ExpNode::ExpNode(lineNum, DataTypeEnum::Void),
m_binaryOpType(type),
m_lValType(DataTypeEnum::Void),
m_rValType(DataTypeEnum::Void)
{
    switch(m_binaryOpType)
    {
    case BinaryOpType::And:
    case BinaryOpType::Or:
    case BinaryOpType::EQ:
    case BinaryOpType::NEQ:
    case BinaryOpType::LT:
    case BinaryOpType::LEQ:
    case BinaryOpType::GT:
    case BinaryOpType::GEQ:
        m_dataType = DataTypeEnum::Bool;
        break;

    case BinaryOpType::Add:
    case BinaryOpType::Sub:
    case BinaryOpType::Mul:
    case BinaryOpType::Div:
    case BinaryOpType::Mod:
    case BinaryOpType::AddAss:
    case BinaryOpType::SubAss:
    case BinaryOpType::MulAss:
    case BinaryOpType::DivAss:
        m_dataType = DataTypeEnum::Int;
        break;

    case BinaryOpType::Ass:
    case BinaryOpType::Index:
        m_dataType = DataTypeEnum::Void;
        break;
    }

    switch(m_binaryOpType)
    {
    case BinaryOpType::And:
    case BinaryOpType::Or:
        m_lValType = DataTypeEnum::Bool;
        m_rValType = DataTypeEnum::Bool;
        break;

    case BinaryOpType::Add:
    case BinaryOpType::Sub:
    case BinaryOpType::Mul:
    case BinaryOpType::Div:
    case BinaryOpType::Mod:
    case BinaryOpType::AddAss:
    case BinaryOpType::SubAss:
    case BinaryOpType::MulAss:
    case BinaryOpType::DivAss:
        m_lValType = DataTypeEnum::Int;
        m_rValType = DataTypeEnum::Int;
        break;
    }
}

void BinaryOpNode::printNode()
{
    switch(m_binaryOpType)
    {
    case BinaryOpType::Ass:
    case BinaryOpType::AddAss:
    case BinaryOpType::SubAss:
    case BinaryOpType::MulAss:
    case BinaryOpType::DivAss:
        std::cout << "Assign: ";
        break;
    default:
        std::cout << "Op: ";
    }
    std::cout << binaryOpTypeToStr(m_binaryOpType);
}