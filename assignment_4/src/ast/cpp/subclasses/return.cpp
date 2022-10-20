#include "../../hpp/subclasses/return.hpp"

#include "../../hpp/node.hpp"

#include <string>

ReturnNode::ReturnNode(unsigned int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string ReturnNode::toString(bool printType)
{ 
    return "Return";
}

