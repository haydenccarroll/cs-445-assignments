#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"


#include <iostream>

class CompoundStmtNode : public ASTNode
{
public:
    CompoundStmtNode(unsigned int lineNum, bool isFromFunction=false);
    void printNode() { std::cout << "Compound"; }
    NodeType getNodeType() { return NodeType::CompoundStmtNode; }

    void setIsFromFunction(bool isFromFunction) { m_isFromFunction = isFromFunction; }
    bool getIsFromFunction() { return m_isFromFunction; }

private:
    bool m_isFromFunction;
};
