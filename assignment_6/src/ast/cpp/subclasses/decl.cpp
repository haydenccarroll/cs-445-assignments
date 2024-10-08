#include "../../hpp/subclasses/decl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/include.hpp"

#include <string>
#include <iostream>

DeclNode::DeclNode(int lineNum, std::string name, DataType dataType) :
ASTNode::ASTNode(lineNum),
m_name(name),
m_dataType(dataType),
m_uses(0)
{
}

void DeclNode::use(int lineNum, bool warnUninit)
{
    m_uses++;
}