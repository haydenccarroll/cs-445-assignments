#include "../../hpp/subclasses/compoundStmt.hpp"

#include "../../hpp/node.hpp"

#include <string>

CompoundStmtNode::CompoundStmtNode(int lineNum) :
ASTNode::ASTNode(lineNum)
{
}

std::string CompoundStmtNode::toString(bool printType)
{ 
    return "Compound";
}