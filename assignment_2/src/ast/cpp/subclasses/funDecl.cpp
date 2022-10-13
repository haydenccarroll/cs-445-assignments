#include "../../hpp/subclasses/funDecl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"

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
    std::cout << "Func: " << m_funcName << " returns ";
    m_returnType.print(false);
}
