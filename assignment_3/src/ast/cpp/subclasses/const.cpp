#include "../../hpp/subclasses/const.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include "../../../types/types.hpp"

#include <string>
#include <iostream>

ConstNode::ConstNode(unsigned int lineNum, int value) 
: ExpNode::ExpNode(lineNum, DataTypeEnum::Int),
m_constType(ConstType::Int),
m_intValue(value),
m_charValue(0),
m_boolValue(false),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, char value) 
: ExpNode::ExpNode(lineNum, DataTypeEnum::Char),
m_constType(ConstType::Char),
m_intValue(0),
m_charValue(value),
m_boolValue(false),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, bool value) 
: ExpNode::ExpNode(lineNum, DataTypeEnum::Bool),
m_constType(ConstType::Bool),
m_intValue(0),
m_charValue(0),
m_boolValue(value),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, std::string value) 
: ExpNode::ExpNode(lineNum, DataType(DataTypeEnum::Char, true)),
m_constType(ConstType::String),
m_intValue(0),
m_charValue(0),
m_boolValue(false),
m_stringValue(value)
{
}

void ConstNode::printNode()
{
    std::cout << "Const ";
    std::cout << std::boolalpha;
    switch(m_constType)
    {
    case ConstType::Bool:
        std::cout << m_boolValue;
        break;
    case ConstType::Int:
        std::cout << m_intValue;
        break;
    case ConstType::Char:
        std::cout << "'" << m_charValue << "'";
        break;
    case ConstType::String:
        std::cout << "is array \"" << m_stringValue << "\"";
        break;
    }
}

void ConstNode::printTypedNode()
{
    std::cout << "Const ";
    std::cout << std::boolalpha;
    switch(m_constType)
    {
    case ConstType::Bool:
        std::cout << m_boolValue;
        break;
    case ConstType::Int:
        std::cout << m_intValue;
        break;
    case ConstType::Char:
        std::cout << "'" << m_charValue << "'";
        break;
    case ConstType::String:
        std::cout << "is array \"" << m_stringValue << "\"";
        break;
    }

    std::cout << " " << m_dataType.getBasicType().toString();
}
