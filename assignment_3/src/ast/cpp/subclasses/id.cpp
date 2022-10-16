#include "../../hpp/subclasses/id.hpp"

#include "../../hpp/subclasses/exp.hpp"

#include <string>

IdNode::IdNode(unsigned int lineNum, std::string idName) :
ExpNode::ExpNode(lineNum, DataTypeEnum::Void),
m_idName(idName)
{
}
