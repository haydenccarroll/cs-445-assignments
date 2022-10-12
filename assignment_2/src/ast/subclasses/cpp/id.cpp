#include "../hpp/id.hpp"

#include "../../node.hpp"

#include <string>

IdNode::IdNode(unsigned int lineNum, std::string idName, bool isArray) :
ASTNode::ASTNode(lineNum),
m_idName(idName),
m_isArray(isArray),
m_arraySize(0)
{
}

IdNode::IdNode(unsigned int lineNum, std::string idName, bool isArray, int arraySize) :
ASTNode::ASTNode(lineNum),
m_idName(idName),
m_isArray(isArray),
m_arraySize(arraySize)
{
}
