#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class ForNode : public ASTNode
{
public:
    ForNode(unsigned int lineNum);
    void printNode() { std::cout << "For"; }
    NodeType getNodeType() { return NodeType::ForNode; }
    virtual void printTypedNode() { printNode(); }

private:
};
