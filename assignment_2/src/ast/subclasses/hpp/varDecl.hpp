#pragma once

#include "../../node.hpp"
#include "../../../types/types.hpp"

class VarDeclNode : public ASTNode
{
public:
    VarDeclNode(unsigned int lineNum, std::string varName, DataType type, bool isStatic=false);
    void printNode();
    void setTypeSpec(DataTypeEnum type);
    void setStatic(bool isStatic);

private:
    std::string m_varName;
    DataType m_dataType;
    bool m_isStatic;
};
