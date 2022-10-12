#include "../hpp/assignOp.hpp"

#include "../../node.hpp"
#include "../../../types.hpp"

AssignOpNode::AssignOpNode(unsigned int lineNum, AssignOpType type) 
: ASTNode::ASTNode(lineNum),
m_assignOpType(type)
{
}
