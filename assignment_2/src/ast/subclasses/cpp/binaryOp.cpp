#include "../hpp/binaryOp.hpp"

#include "../../node.hpp"
#include "../../../types.hpp"

BinaryOpNode::BinaryOpNode(unsigned int lineNum, BinaryOpType type) 
: ASTNode::ASTNode(lineNum),
m_binaryOpType(type)
{
}
