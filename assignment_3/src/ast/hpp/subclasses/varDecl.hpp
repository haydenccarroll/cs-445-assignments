#pragma once

#include "decl.hpp"
#include "../../../types/types.hpp"

class VarDeclNode : public DeclNode
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
    VarDeclNode(unsigned int lineNum, std::string varName, DataType type, bool isStatic=false, bool isParam=false);
    
    void printNode();

    bool isParam() { return m_isParam; }

    virtual NodeType getNodeType() { return NodeType::VarDeclNode; }
    /**
     * @brief sets the concrete type of itself and all siblings
     * 
     * @param type concrete type
     */
    void setTypeSpec(DataTypeEnum type);

    void setInitialized(bool isInitialized) { m_isInitialized = isInitialized; }
    bool isInitialized() { return m_isInitialized; }
    void use(unsigned int lineNum);
    unsigned int getUsage() { return m_uses; }

    /**
     * @brief sets the m_isStatic member for itself and all siblings
     * 
     * @param isStatic true if static else false
     */
    void setStatic(bool isStatic);


private:
    bool m_isStatic;
    bool m_isParam;
    bool m_isInitialized;
    unsigned int m_uses;
};
