#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

#include <iostream>

class ExpNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Id Node object
     * 
     * @param lineNum 
     * @param idName name of id
     * @param isArray true if id is an array
     */
    ExpNode(unsigned int lineNum, DataType type);
    void setExpType(DataType type);
    DataType getExpType() { return m_dataType; }

    virtual void printNode() = 0;
    virtual NodeType getNodeType() = 0;
protected:
    DataType m_dataType;
};
