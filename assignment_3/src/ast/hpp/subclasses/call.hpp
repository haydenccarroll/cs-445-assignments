#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <string>
#include <iostream>

class CallNode : public ASTNode
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

private:
    std::string m_functionName;
};
