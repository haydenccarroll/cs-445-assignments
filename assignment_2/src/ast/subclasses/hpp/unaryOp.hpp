#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

class UnaryOpNode : public ASTNode
{
public:
    UnaryOpNode(unsigned int lineNum, UnaryOpType type);



private:
    const UnaryOpType m_unaryOpType;
};
