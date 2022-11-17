#include "../../hpp/subclasses/varDecl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/include.hpp"
#include "../../../error/include.hpp"

#include <string>
#include <sstream>

VarDeclNode::VarDeclNode(int lineNum, std::string varName,
                         DataType type, bool isStatic, bool isParam) :
DeclNode::DeclNode(lineNum, varName, type),
m_isStatic(isStatic),
m_isInitialized(false),
m_isParam(isParam)
{
}

std::string VarDeclNode::toString(bool printType)
{
    std::stringstream ss;

    if (m_isParam)
    {
        ss << "Parm: ";
    } else
    {
        ss << "Var: ";
    }
    ss << m_name << " " << m_dataType.toString();

    return ss.str();
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

void VarDeclNode::use(int lineNum, bool warnUninit)
{
    if (m_isInitialized == false && m_uses == 0 && warnUninit)
    {
        std::stringstream ss;
        ss << "Variable '" << m_name << "' may be uninitialized when used here.";
        Error::warning(lineNum, ss.str());
    }
    m_uses++;
}
