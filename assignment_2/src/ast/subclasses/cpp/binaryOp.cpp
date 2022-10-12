#include "../hpp/binaryOp.hpp"

#include "../../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

BinaryOpNode::BinaryOpNode(unsigned int lineNum, BinaryOpType type) 
: ASTNode::ASTNode(lineNum),
m_binaryOpType(type)
{
}

void BinaryOpNode::printNode()
{
    std::cout << "Op: " << binaryOpTypeToStr(m_binaryOpType);
}