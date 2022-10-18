#include "../../hpp/subclasses/unaryOp.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include "../../../types/types.hpp"

#include <string>

UnaryOpNode::UnaryOpNode(unsigned int lineNum, UnaryOpType type) 
: ExpNode::ExpNode(lineNum, DataTypeEnum::Void),
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

void UnaryOpNode::printNode()
{ 
    switch(m_unaryOpType)
    {
    case UnaryOpType::Inc:
    case UnaryOpType::Dec:
        std::cout << "Assign: ";
        break;
    default:
        std::cout << "Op: ";
    }
    std::cout << unaryOpTypeToStr(m_unaryOpType); 
}

void UnaryOpNode::printTypedNode()
{ 
    switch(m_unaryOpType)
    {
    case UnaryOpType::Inc:
    case UnaryOpType::Dec:
        std::cout << "Assign: ";
        break;
    default:
        std::cout << "Op: ";
    }
    std::cout << unaryOpTypeToStr(m_unaryOpType)
              << " " << m_dataType.toString();
}

