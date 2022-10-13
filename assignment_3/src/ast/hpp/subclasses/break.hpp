#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class BreakNode : public ASTNode
{
public:
    BreakNode(unsigned int lineNum);
    void printNode() { std::cout << "Break"; }
    NodeType getNodeType() { return NodeType::BreakNode; }

private:
};
