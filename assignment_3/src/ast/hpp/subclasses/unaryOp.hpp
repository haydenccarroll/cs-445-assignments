#pragma once

#include "exp.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class UnaryOpNode : public ExpNode
{
public:
    /**
     * @brief Construct a new Unary Op Node object
     * 
     * @param lineNum 
     * @param type type of unary operator used
     */
    UnaryOpNode(unsigned int lineNum, UnaryOpType type);
    void printNode();
    NodeType getNodeType() { return NodeType::UnaryOpNode; }
    UnaryOpType getOperatorType() { return m_unaryOpType; }


private:
    const UnaryOpType m_unaryOpType;
};
