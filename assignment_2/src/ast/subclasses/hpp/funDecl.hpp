#pragma once

#include "../../node.hpp"
#include "../../../types.hpp"

class FunDeclNode : public ASTNode
{
public:
    FunDeclNode(unsigned int lineNum, std::string funcName, DataType returnType);

private:
    std::string m_funcName;
    DataType m_returnType;
};
