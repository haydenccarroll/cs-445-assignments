#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

#include <iostream>

class CompoundStmtNode : public ASTNode
{
public:
    CompoundStmtNode(unsigned int lineNum);
    void printNode() { std::cout << "Compound"; }

private:
};
