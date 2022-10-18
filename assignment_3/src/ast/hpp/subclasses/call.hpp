#pragma once

#include "exp.hpp"
#include "../../../types/types.hpp"

#include <string>
#include <iostream>

class CallNode : public ExpNode
{
public:
    /**
     * @brief Construct a new Call Node object
     * 
     * @param lineNum 
     * @param functionName name of function that was called
     */
    CallNode(unsigned int lineNum, std::string functionName);
    void printNode() { std::cout << "Call: " << m_functionName; }
    NodeType getNodeType() { return NodeType::CallNode; }
    std::string getFunName() { return m_functionName; }
    virtual void printTypedNode();

private:
    std::string m_functionName;
};
