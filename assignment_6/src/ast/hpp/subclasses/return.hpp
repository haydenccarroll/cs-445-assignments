#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

class ReturnNode : public ASTNode
{
public:
    ReturnNode(int lineNum);
    std::string toString(bool printType=false) override;
    NodeType getNodeType() override { return NodeType::ReturnNode; }

private:
};
