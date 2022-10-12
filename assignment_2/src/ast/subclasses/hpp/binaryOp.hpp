#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

class BinaryOpNode : public ASTNode
{
public:
    BinaryOpNode(unsigned int lineNum, BinaryOpType type);



private:
    const BinaryOpType m_binaryOpType;
};
