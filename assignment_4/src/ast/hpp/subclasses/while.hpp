#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

class WhileNode : public ASTNode
{
public:
    WhileNode(unsigned int lineNum);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::WhileNode; }

private:
};
