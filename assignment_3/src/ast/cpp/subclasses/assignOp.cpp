#include "../../hpp/subclasses/assignOp.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"

#include <iostream>


AssignOpNode::AssignOpNode(unsigned int lineNum, AssignOpType type) 
: ASTNode::ASTNode(lineNum),
m_assignOpType(type)
{
}

void AssignOpNode::printNode()
{
    std::cout << "Assign: " << assignOpTypeToStr(m_assignOpType);
}
