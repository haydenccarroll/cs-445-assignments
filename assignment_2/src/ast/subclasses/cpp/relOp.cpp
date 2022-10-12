#include "../hpp/relOp.hpp"

#include "../../node.hpp"
#include "../../../types.hpp"

RelOpNode::RelOpNode(unsigned int lineNum, RelOpType type) 
: ASTNode::ASTNode(lineNum),
m_relOpType(type)
{
}
