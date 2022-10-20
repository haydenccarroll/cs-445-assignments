#include "../../hpp/subclasses/const.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include "../../../types/include.hpp"

#include <string>
#include <sstream>

ConstNode::ConstNode(unsigned int lineNum, int value) 
: ExpNode::ExpNode(lineNum, DataType(DataTypeEnum::Int)),
m_constType(ConstType::Int),
m_intValue(value),
m_charValue(0),
m_boolValue(false),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, char value) 
: ExpNode::ExpNode(lineNum, DataType(DataTypeEnum::Char)),
m_constType(ConstType::Char),
m_intValue(0),
m_charValue(value),
m_boolValue(false),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, bool value) 
: ExpNode::ExpNode(lineNum, DataType(DataTypeEnum::Bool)),
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

std::string ConstNode::toString(bool printType)
{
    std::stringstream ss;
    ss << "Const ";
    ss << std::boolalpha;
    switch(m_constType)
    {
    case ConstType::Bool:
        ss << m_boolValue;
        break;
    case ConstType::Int:
        ss << m_intValue;
        break;
    case ConstType::Char:
        ss << "'" << m_charValue << "'";
        break;
    case ConstType::String:
        ss << "is array \"" << m_stringValue << "\"";
        break;
    }

    if (printType)
    {
        ss << " " << m_dataType.getBasicType().toString();
    }

    return ss.str();
}
