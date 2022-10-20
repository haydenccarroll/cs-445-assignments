#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

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

    virtual std::string toString(bool printType=false) = 0;
    virtual NodeType getNodeType() = 0;

protected:
    DataType m_dataType;
};
