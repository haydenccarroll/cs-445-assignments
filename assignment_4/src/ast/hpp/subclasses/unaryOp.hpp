#pragma once

#include "exp.hpp"
#include "../../../types/include.hpp"

#include <string>

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
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::UnaryOpNode; }
    UnaryOpType getOperatorType() { return m_unaryOpType; }


private:
    const UnaryOpType m_unaryOpType;
};
