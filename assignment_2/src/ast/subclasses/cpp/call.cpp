#include "../hpp/call.hpp"

#include "../../node.hpp"
#include <string>

CallNode::CallNode(unsigned int lineNum, std::string functionName) :
ASTNode::ASTNode(lineNum),
m_functionName(functionName)
{
}
