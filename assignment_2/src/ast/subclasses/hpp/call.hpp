#pragma once

#include "../../node.hpp"
#include <string>

class CallNode : public ASTNode
{
public:
    CallNode(unsigned int lineNum, std::string functionName);

private:
    std::string m_functionName;
};
