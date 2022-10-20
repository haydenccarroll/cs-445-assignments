#include "../../hpp/subclasses/binaryOp.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include "../../../types/include.hpp"

#include <sstream>
#include <string>

BinaryOpNode::BinaryOpNode(unsigned int lineNum, BinaryOpType type) : 
ExpNode::ExpNode(lineNum, DataTypeEnum::None),
m_binaryOpType(type)
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
}

std::string BinaryOpNode::toString(bool printType)
{
    std::stringstream ss;
    switch(m_binaryOpType)
    {
    case BinaryOpType::Ass:
    case BinaryOpType::AddAss:
    case BinaryOpType::SubAss:
    case BinaryOpType::MulAss:
    case BinaryOpType::DivAss:
        ss << "Assign: ";
        break;
    default:
        ss << "Op: ";
    }
    ss << binaryOpTypeToStr(m_binaryOpType);
    if (printType)
    {
        ss << " " << m_dataType.toString();
    }

    return ss.str();
}
