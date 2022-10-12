#pragma once

#include "../../node.hpp"
#include "../../../types/types.hpp"

class ParamNode : public ASTNode
{
public:
    ParamNode(unsigned int lineNum, std::string paramName, DataType dataType);
    void printNode();
    void setTypeSpec(DataTypeEnum type);

private:
    std::string m_paramName;
    DataType m_dataType;
};
