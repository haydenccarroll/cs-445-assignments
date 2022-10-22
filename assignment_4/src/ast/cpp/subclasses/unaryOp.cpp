#include "../../hpp/subclasses/unaryOp.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include "../../../types/include.hpp"

#include <string>
#include <sstream>

UnaryOpNode::UnaryOpNode(int lineNum, UnaryOpType type) 
: ExpNode::ExpNode(lineNum, DataTypeEnum::None),
m_unaryOpType(type)
{
    switch(m_unaryOpType)
    {
    case UnaryOpType::Not:
        setExpType(DataTypeEnum::Bool);
        break;
    default:
        setExpType(DataTypeEnum::Int);
        break;
    }
}

std::string UnaryOpNode::toString(bool printType)
{ 
    std::stringstream ss;

    switch(m_unaryOpType)
    {
    case UnaryOpType::Inc:
    case UnaryOpType::Dec:
        ss << "Assign: ";
        break;
    default:
        ss << "Op: ";
    }
    ss << unaryOpTypeToStr(m_unaryOpType);
    if (printType)
    {
        ss << " " << m_dataType.toString();
    }

    return ss.str();
}
