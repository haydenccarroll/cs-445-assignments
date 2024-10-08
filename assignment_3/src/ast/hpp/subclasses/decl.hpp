#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

class DeclNode : public ASTNode
{
public:
    DeclNode(unsigned int lineNum, std::string name, DataType dataType);
    virtual void printNode() = 0;
    virtual NodeType getNodeType() = 0;


    /**
     * @brief returns name of function
     * 
     * @return std::string function name member
     */
    std::string getName() { return m_name; }
    DataType getDataType() { return m_dataType; }
    virtual void printTypedNode() { printNode(); }

protected:
    std::string m_name;
    DataType m_dataType;
};
