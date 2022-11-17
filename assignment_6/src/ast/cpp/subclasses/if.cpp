#include "../../hpp/subclasses/if.hpp"

#include "../../hpp/node.hpp"

#include <string>

IfNode::IfNode(int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string IfNode::toString(bool printType)
{ 
    return "If";
}
