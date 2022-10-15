#pragma once

#include "../node.hpp"
#include "../../../types/types.hpp"

class VarDeclNode : public ASTNode
{
public:
    /**
     * @brief Construct a new Var Decl Node object
     * 
     * @param lineNum 
     * @param varName variable name
     * @param type data type of the variable
     * @param isStatic if variable is static, defaults to false
     */
    VarDeclNode(unsigned int lineNum, std::string varName, DataType type, bool isStatic=false);
    
    void printNode();

    NodeType getNodeType() { return NodeType::VarDeclNode; }
    /**
     * @brief sets the concrete type of itself and all siblings
     * 
     * @param type concrete type
     */
    void setTypeSpec(DataTypeEnum type);

    /**
     * @brief sets the m_isStatic member for itself and all siblings
     * 
     * @param isStatic true if static else false
     */
    void setStatic(bool isStatic);

    /**
     * @brief gets the variable name
     * 
     * @return std::string m_varName member
     */
    std::string getVarName() { return m_varName; }

private:
    std::string m_varName;
    DataType m_dataType;
    bool m_isStatic;
};
