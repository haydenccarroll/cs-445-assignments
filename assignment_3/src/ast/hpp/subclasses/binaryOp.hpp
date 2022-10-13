#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

class BinaryOpNode : public ASTNode
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

private:
    const BinaryOpType m_binaryOpType;
};
