#include "../../hpp/subclasses/while.hpp"

#include "../../hpp/node.hpp"

#include <string>

WhileNode::WhileNode(int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string WhileNode::toString(bool printType)
{ 
    return "While";
}
