#include "../../hpp/subclasses/relOp.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"

RelOpNode::RelOpNode(unsigned int lineNum, RelOpType type) 
: ASTNode::ASTNode(lineNum),
m_relOpType(type)
{
}
