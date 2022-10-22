#include "../../hpp/subclasses/exp.hpp"

#include "../../hpp/node.hpp"

#include <string>

ExpNode::ExpNode(int lineNum, DataType type) :
ASTNode::ASTNode(lineNum),
m_dataType(type)
{
}

void ExpNode::setExpType(DataType type)
{
    m_dataType = type;
}
