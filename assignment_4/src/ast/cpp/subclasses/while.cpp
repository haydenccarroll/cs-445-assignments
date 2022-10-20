#include "../../hpp/subclasses/while.hpp"

#include "../../hpp/node.hpp"

#include <string>

WhileNode::WhileNode(unsigned int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string WhileNode::toString(bool printType)
{ 
    return "While";
}
