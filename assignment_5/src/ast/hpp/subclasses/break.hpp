#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

class BreakNode : public ASTNode
{
public:
    BreakNode(int lineNum);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::BreakNode; }

private:
};
