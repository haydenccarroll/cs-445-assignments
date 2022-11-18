#pragma once

#include "decl.hpp"
#include "../../../types/include.hpp"

#include <string>

class VarDeclNode : public DeclNode
{
public:
    VarDeclNode(int lineNum, std::string varName, DataType type, bool isStatic=false, bool isParam=false);
    
    std::string toString(bool printType=false) override;
    bool isParam() { return m_isParam; }
    NodeType getNodeType() override { return NodeType::VarDeclNode; }
    void setTypeSpec(DataTypeEnum type);
    void setInitialized(bool isInitialized) { m_isInitialized = isInitialized;}
    bool isInitialized() { return m_isInitialized; }
    void setStatic(bool isStatic);
    bool isStatic() { return m_isStatic; }
    void use(int lineNum, bool warnUninit=true) override;

private:
    bool m_isStatic;
    bool m_isParam;
    bool m_isInitialized;
};
