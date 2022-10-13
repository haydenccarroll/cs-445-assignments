#include "../../hpp/subclasses/call.hpp"

#include "../../hpp/node.hpp"
#include <string>

CallNode::CallNode(unsigned int lineNum, std::string functionName) :
ASTNode::ASTNode(lineNum),
m_functionName(functionName)
{
}
