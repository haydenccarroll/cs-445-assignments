#include "../../hpp/subclasses/range.hpp"

#include "../../hpp/node.hpp"

#include <string>

RangeNode::RangeNode(unsigned int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string RangeNode::toString(bool printType)
{ 
    return "Range";
}
