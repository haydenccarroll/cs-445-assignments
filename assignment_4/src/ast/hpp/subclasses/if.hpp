#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class IfNode : public ASTNode
{
public:
    IfNode(unsigned int lineNum);
    void printNode() { std::cout << "If"; }
    NodeType getNodeType() { return NodeType::IfNode; }
    virtual void printTypedNode() { printNode(); }

private:
};
