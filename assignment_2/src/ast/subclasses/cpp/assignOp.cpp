#include "../hpp/assignOp.hpp"

#include "../../node.hpp"
#include "../../../types/types.hpp"

AssignOpNode::AssignOpNode(unsigned int lineNum, AssignOpType type) 
: ASTNode::ASTNode(lineNum),
m_assignOpType(type)
{
}

void AssignOpNode::printNode()
{
    std::cout << "Assign: " << assignOpTypeToStr(m_assignOpType);
}
