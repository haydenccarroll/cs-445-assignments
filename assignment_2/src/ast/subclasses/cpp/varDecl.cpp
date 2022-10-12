#include "../hpp/varDecl.hpp"

#include "../../node.hpp"
#include "../../../types.hpp"

#include <string>
#include <iostream>

VarDeclNode::VarDeclNode(unsigned int lineNum, std::string varName, DataType type) :
ASTNode::ASTNode(lineNum),
m_varName(varName),
m_type(type)
{
}

void VarDeclNode::printNode()
{
    std::cout << "Var: " << m_varName << " of type " << dataTypeToStr(m_type);
}
