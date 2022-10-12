#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

class VarDeclNode : public ASTNode
{
public:
    VarDeclNode(unsigned int lineNum, std::string varName, DataType type);
    void printNode();

private:
    std::string m_varName;
    DataType m_type;
};
