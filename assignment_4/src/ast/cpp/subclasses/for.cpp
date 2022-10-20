#include "../../hpp/subclasses/for.hpp"

#include "../../hpp/node.hpp"

#include <string>

ForNode::ForNode(unsigned int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string ForNode::toString(bool printType)
{ 
    return "For";
}
