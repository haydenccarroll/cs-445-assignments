#pragma once

#include "exp.hpp"
#include "../../../types/types.hpp"

class BinaryOpNode : public ExpNode
{
public:
    /**
     * @brief Construct a new Binary Op Node object
     * 
     * @param lineNum 
     * @param type type of binary operator used
     */
    BinaryOpNode(unsigned int lineNum, BinaryOpType type);
    void printNode();
    NodeType getNodeType() { return NodeType::BinaryOpNode; }
    BinaryOpType getOperatorType() { return m_binaryOpType; }
    virtual void printTypedNode();


private:
    const BinaryOpType m_binaryOpType;
};
