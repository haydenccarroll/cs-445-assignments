#include "../../hpp/subclasses/id.hpp"

#include "../../hpp/subclasses/exp.hpp"

#include <string>

IdNode::IdNode(unsigned int lineNum, std::string idName) :
ExpNode::ExpNode(lineNum, DataTypeEnum::None),
m_idName(idName)
{
}


void IdNode::printNode()
{
    std::cout << "Id: " << m_idName;
}

void IdNode::printTypedNode()
{
    std::cout << "Id: " << m_idName << " "
              << m_dataType.getBasicType().toString();
}
