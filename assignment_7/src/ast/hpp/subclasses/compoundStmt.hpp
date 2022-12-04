#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"


#include <string>

class CompoundStmtNode : public ASTNode
{
public:
    CompoundStmtNode(int lineNum);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::CompoundStmtNode; }
private:
};
