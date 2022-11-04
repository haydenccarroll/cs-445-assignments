#pragma once

#include "../node.hpp"
#include "../../../types/include.hpp"

#include <string>

class DeclNode : public ASTNode
{
public:
    DeclNode(int lineNum, std::string name, DataType dataType);
    virtual std::string toString(bool printType=false) = 0;
    virtual NodeType getNodeType() = 0;


    /**
     * @brief returns name of function
     * 
     * @return std::string function name member
     */
    std::string getName() { return m_name; }
    DataType getDataType() { return m_dataType; }

    virtual void use(int lineNum, bool warnUninit=true);
    unsigned int getUsage() { return m_uses; }

protected:
    std::string m_name;
    DataType m_dataType;
    unsigned int m_uses;
};
