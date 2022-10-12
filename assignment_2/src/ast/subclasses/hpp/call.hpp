#pragma once

#include "../../node.hpp"
#include <string>
#include <iostream>

class CallNode : public ASTNode
{
public:
    CallNode(unsigned int lineNum, std::string functionName);
    void printNode() { std::cout << "Call: " << m_functionName; }

private:
    std::string m_functionName;
};
