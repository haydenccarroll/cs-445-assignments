#include "../../hpp/subclasses/call.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include <string>

CallNode::CallNode(unsigned int lineNum, std::string funName) : 
ExpNode::ExpNode(lineNum, DataTypeEnum::Void),
m_functionName(funName)
{
}
