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
    DataType getLValType() { return m_lValType; }
    DataType getRValType() { return m_rValType; }
    BinaryOpType getOperatorType() { return m_binaryOpType; }


private:
    const BinaryOpType m_binaryOpType;
    DataType m_lValType;
    DataType m_rValType;
};
