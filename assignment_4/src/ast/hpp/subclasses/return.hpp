#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class ReturnNode : public ASTNode
{
public:
    ReturnNode(unsigned int lineNum);
    void printNode() { std::cout << "Return"; }
    NodeType getNodeType() { return NodeType::ReturnNode; }
    virtual void printTypedNode() { printNode(); }

private:
};
