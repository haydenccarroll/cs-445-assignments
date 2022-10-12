#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

class AssignOpNode : public ASTNode
{
public:
    AssignOpNode(unsigned int lineNum, AssignOpType type);

private:
    const AssignOpType m_assignOpType;
};
