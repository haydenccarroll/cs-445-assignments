#include "../hpp/unaryOp.hpp"

#include "../../node.hpp"
#include "../../../types/types.hpp"

#include <string>

UnaryOpNode::UnaryOpNode(unsigned int lineNum, UnaryOpType type) 
: ASTNode::ASTNode(lineNum),
m_unaryOpType(type)
{
}
