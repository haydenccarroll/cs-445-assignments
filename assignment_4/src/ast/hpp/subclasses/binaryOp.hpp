#pragma once

#include "exp.hpp"
#include "../../../types/include.hpp"

#include <string>

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
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::BinaryOpNode; }
    BinaryOpType getOperatorType() { return m_binaryOpType; }


private:
    const BinaryOpType m_binaryOpType;
};
