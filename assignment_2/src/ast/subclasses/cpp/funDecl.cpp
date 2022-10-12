#include "../hpp/funDecl.hpp"

#include "../../node.hpp"
#include "../../../types.hpp"

#include <string>
#include <iostream>

FunDeclNode::FunDeclNode(unsigned int lineNum, std::string funcName, DataType returnType) :
ASTNode::ASTNode(lineNum),
m_funcName(funcName),
m_returnType(returnType)
{
}

void FunDeclNode::printNode()
{
    std::cout << "Func: " << m_funcName << " returns type " << dataTypeToStr(m_returnType);
}
