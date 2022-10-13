#pragma once

#include "../node.hpp"
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

private:
    std::string m_functionName;
};
