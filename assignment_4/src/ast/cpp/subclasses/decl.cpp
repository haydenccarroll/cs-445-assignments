#include "../../hpp/subclasses/decl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"

#include <string>
#include <iostream>

DeclNode::DeclNode(unsigned int lineNum, std::string name, DataType dataType) :
ASTNode::ASTNode(lineNum),
m_name(name),
m_dataType(dataType)
{
}
