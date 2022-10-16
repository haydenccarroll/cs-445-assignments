#include "../../hpp/subclasses/compoundStmt.hpp"

#include "../../hpp/node.hpp"


CompoundStmtNode::CompoundStmtNode(unsigned int lineNum, bool isFromFunction) :
ASTNode::ASTNode(lineNum),
m_isFromFunction(isFromFunction)
{
}
