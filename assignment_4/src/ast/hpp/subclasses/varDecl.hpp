#pragma once

#include "decl.hpp"
#include "../../../types/include.hpp"

#include <string>

class VarDeclNode : public DeclNode
{
public:
    VarDeclNode(unsigned int lineNum, std::string varName, DataType type, bool isStatic=false, bool isParam=false);
    
    std::string toString(bool printType=false) override;
    bool isParam() { return m_isParam; }
    NodeType getNodeType() override { return NodeType::VarDeclNode; }
    void setTypeSpec(DataTypeEnum type);
    void setInitialized(bool isInitialized) { m_isInitialized = isInitialized;}
    bool isInitialized() { return m_isInitialized; }
    void use(unsigned int lineNum, bool warnUninit=true);
    unsigned int getUsage() { return m_uses; }
    void setStatic(bool isStatic);


private:
    bool m_isStatic;
    bool m_isParam;
    bool m_isInitialized;
    unsigned int m_uses;
};
