#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

class IfNode : public ASTNode
{
public:
    IfNode(unsigned int lineNum);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::IfNode; }

private:
};
