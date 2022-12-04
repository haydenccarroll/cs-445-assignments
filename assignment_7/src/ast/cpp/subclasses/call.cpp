#include "../../hpp/subclasses/call.hpp"

#include "../../hpp/subclasses/exp.hpp"
#include <string>
#include <sstream>

CallNode::CallNode(int lineNum, std::string funName) : 
ExpNode::ExpNode(lineNum, DataTypeEnum::None),
m_functionName(funName)
{
}

std::string CallNode::toString(bool printType)
{ 
    std::stringstream ss;
    ss << "Call: " << m_functionName;
    if (printType)
    {
        ss << " " << m_dataType.toString();
    }

    return ss.str();
}
