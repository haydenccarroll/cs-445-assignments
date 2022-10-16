#include "../../hpp/subclasses/varDecl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"

#include <string>
#include <iostream>

VarDeclNode::VarDeclNode(unsigned int lineNum, std::string varName, DataType type, bool isStatic) :
DeclNode::DeclNode(lineNum, varName, type),
m_isStatic(isStatic)
{
}

void VarDeclNode::printNode()
{
    std::cout << "Var: " << m_name << " ";
    m_dataType.print(true, m_isStatic);
}

void VarDeclNode::setTypeSpec(DataTypeEnum type)
{
    m_dataType.setTypeSpec(type);
    if (m_sibling != nullptr)
    {
        VarDeclNode* varDeclSibling = dynamic_cast<VarDeclNode*>(m_sibling);
        varDeclSibling->setTypeSpec(type);
    }
}

void VarDeclNode::setStatic(bool isStatic)
{
    m_isStatic = isStatic;
    if (m_sibling != nullptr)
    {
        VarDeclNode* varDeclSibling = dynamic_cast<VarDeclNode*>(m_sibling);
        varDeclSibling->setStatic(isStatic);
    }
}
