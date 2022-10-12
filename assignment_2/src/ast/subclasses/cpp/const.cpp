#include "../hpp/const.hpp"

#include "../../node.hpp"
#include "../../../types.hpp"

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
