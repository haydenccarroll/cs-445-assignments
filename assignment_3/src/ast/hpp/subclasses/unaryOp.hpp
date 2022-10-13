#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class UnaryOpNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Unary Op Node object
     * 
     * @param lineNum 
     * @param type type of unary operator used
     */
    UnaryOpNode(unsigned int lineNum, UnaryOpType type);
    void printNode() { std::cout << "Op: " << unaryOpTypeToStr(m_unaryOpType); }
    NodeType getNodeType() { return NodeType::UnaryOpNode; }


private:
    const UnaryOpType m_unaryOpType;
};
