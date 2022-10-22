#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

class ForNode : public ASTNode
{
public:
    ForNode(int lineNum);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::ForNode; }

private:
};
