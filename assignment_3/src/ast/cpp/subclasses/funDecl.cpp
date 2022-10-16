#include "../../hpp/subclasses/funDecl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"

#include <string>
#include <iostream>

FunDeclNode::FunDeclNode(unsigned int lineNum, std::string funcName, DataType returnType) :
DeclNode::DeclNode(lineNum, funcName, returnType)
{
}

void FunDeclNode::printNode()
{
    std::cout << "Func: " << m_name << " returns ";
    m_dataType.print(false);
}
