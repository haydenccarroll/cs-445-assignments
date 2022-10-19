#include "../../hpp/subclasses/call.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include <string>

CallNode::CallNode(unsigned int lineNum, std::string funName) : 
ExpNode::ExpNode(lineNum, DataTypeEnum::None),
m_functionName(funName)
{
}

void CallNode::printTypedNode()
{
    std::cout << "Call: " << m_functionName
              << " " << m_dataType.toString();

}
