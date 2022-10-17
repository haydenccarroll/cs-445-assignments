#include "../../hpp/subclasses/varDecl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/types.hpp"
#include "../../../error/error.hpp"

#include <string>
#include <iostream>
#include <sstream>

VarDeclNode::VarDeclNode(unsigned int lineNum, std::string varName,
                         DataType type, bool isStatic, bool isParam) :
DeclNode::DeclNode(lineNum, varName, type),
m_isStatic(isStatic),
m_isInitialized(false),
m_uses(0),
m_isParam(isParam)
{
}

void VarDeclNode::printNode()
{
    if (m_isParam)
    {
        std::cout << "Parm: ";
    } else
    {
        std::cout << "Var: ";
    }
    std::cout << m_name << " ";
    m_dataType.print(true);
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
    m_isInitialized = (isStatic | m_isInitialized);
    if (m_sibling != nullptr)
    {
        VarDeclNode* varDeclSibling = dynamic_cast<VarDeclNode*>(m_sibling);
        varDeclSibling->setStatic(isStatic);
    }
}

void VarDeclNode::use(unsigned int lineNum, bool warnUninit)
{
    if (m_isInitialized == false && m_uses == 0 && warnUninit)
    {
        std::stringstream ss;
        ss << "Variable '" << m_name << "' may be uninitialized when used here.";
        Error::warning(lineNum, ss.str());
    }
    m_uses++;
}
