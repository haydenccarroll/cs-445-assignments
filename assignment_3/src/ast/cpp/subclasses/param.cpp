#include "../../hpp/subclasses/param.hpp"

#include "../../hpp/subclasses/decl.hpp"
#include "../../../types/types.hpp"

#include "../../../error/error.hpp"

#include <string>
#include <iostream>

ParamNode::ParamNode(unsigned int lineNum, std::string paramName, DataType dataType) :
DeclNode::DeclNode(lineNum, paramName, dataType)
{
}

void ParamNode::printNode()
{
    std::cout << "Parm: " << m_name << " ";
    m_dataType.print();
}

void ParamNode::setTypeSpec(DataTypeEnum type)
{
    m_dataType.setTypeSpec(type);
    if (m_sibling != nullptr)
    {
        ParamNode* paramSibling = dynamic_cast<ParamNode*>(m_sibling);
        if (paramSibling == nullptr)
        {
            Error::error(m_sibling->getLineNum(), "dynamic_cast<ParamNode*> failed in TypeSpec(). Node is wrong type.");
        }
        paramSibling->setTypeSpec(type);
    }
}