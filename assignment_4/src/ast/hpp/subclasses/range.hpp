#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

class RangeNode : public ASTNode
{
public:
    RangeNode(unsigned int lineNum);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::RangeNode; }

private:
};
