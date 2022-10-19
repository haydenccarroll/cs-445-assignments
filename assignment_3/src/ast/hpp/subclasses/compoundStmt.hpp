#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"


#include <iostream>

class CompoundStmtNode : public ASTNode
{
public:
    CompoundStmtNode(unsigned int lineNum);
    void printNode() { std::cout << "Compound"; }
    NodeType getNodeType() { return NodeType::CompoundStmtNode; }
    virtual void printTypedNode() { printNode(); }

private:
};
