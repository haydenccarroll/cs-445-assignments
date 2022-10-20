#include "../../hpp/subclasses/break.hpp"

#include "../../hpp/node.hpp"

#include <string>

BreakNode::BreakNode(unsigned int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string BreakNode::toString(bool printType)
{ 
    return "Break";
}
