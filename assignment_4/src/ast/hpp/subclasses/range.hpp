#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class RangeNode : public ASTNode
{
public:
    RangeNode(unsigned int lineNum);
    void printNode() { std::cout << "Range"; }
    NodeType getNodeType() { return NodeType::RangeNode; }
    virtual void printTypedNode() { printNode(); }

private:
};
