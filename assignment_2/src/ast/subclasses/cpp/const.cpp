#include "../hpp/const.hpp"

#include "../../node.hpp"
#include "../../../types/types.hpp"

#include <string>

ConstNode::ConstNode(unsigned int lineNum, ConstType type, int value) 
: ASTNode::ASTNode(lineNum),
m_constType(type),
m_intValue(value),
m_charValue(0),
m_boolValue(false),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, ConstType type, char value) 
: ASTNode::ASTNode(lineNum),
m_constType(type),
m_intValue(0),
m_charValue(value),
m_boolValue(false),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, ConstType type, bool value) 
: ASTNode::ASTNode(lineNum),
m_constType(type),
m_intValue(0),
m_charValue(0),
m_boolValue(value),
m_stringValue("")
{
}

ConstNode::ConstNode(unsigned int lineNum, ConstType type, std::string value) 
: ASTNode::ASTNode(lineNum),
m_constType(type),
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
        std::cout << "\"" << m_stringValue << "\"";
        break;
    }
}
