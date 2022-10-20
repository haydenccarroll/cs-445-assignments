#pragma once

#include "exp.hpp"
#include "../../../types/include.hpp"

#include <string>

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
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::CallNode; }
    std::string getFunName() { return m_functionName; }

private:
    std::string m_functionName;
};
