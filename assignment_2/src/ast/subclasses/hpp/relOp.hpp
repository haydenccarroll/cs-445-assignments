#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

class RelOpNode : public ASTNode
{
public:
    RelOpNode(unsigned int lineNum, RelOpType type);

private:
    const RelOpType m_relOpType;
};
