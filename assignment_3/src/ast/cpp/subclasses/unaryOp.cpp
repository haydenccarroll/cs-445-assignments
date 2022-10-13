#include "../../hpp/subclasses/unaryOp.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"

#include <string>

UnaryOpNode::UnaryOpNode(unsigned int lineNum, UnaryOpType type) 
: ASTNode::ASTNode(lineNum),
m_unaryOpType(type)
{
}
