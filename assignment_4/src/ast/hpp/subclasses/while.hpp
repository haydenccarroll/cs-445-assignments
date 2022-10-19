#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class WhileNode : public ASTNode
{
public:
    WhileNode(unsigned int lineNum);
    void printNode() { std::cout << "While"; }
    NodeType getNodeType() { return NodeType::WhileNode; }
    virtual void printTypedNode() { printNode(); }

private:
};
