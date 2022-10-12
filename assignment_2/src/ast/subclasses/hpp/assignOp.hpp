#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

class AssignOpNode : public ASTNode
{
public:
    AssignOpNode(unsigned int lineNum, AssignOpType type);
    void printNode();

private:
    const AssignOpType m_assignOpType;
};
