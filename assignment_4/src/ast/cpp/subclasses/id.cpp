#include "../../hpp/subclasses/id.hpp"

#include "../../hpp/subclasses/exp.hpp"

#include <string>
#include <sstream>

IdNode::IdNode(int lineNum, std::string idName) :
ExpNode::ExpNode(lineNum, DataTypeEnum::None),
m_idName(idName)
{
}


std::string IdNode::toString(bool printType)
{
    std::stringstream ss;
    ss << "Id: " << m_idName;
    if (printType)
    {
        ss << " " << m_dataType.getBasicType().toString();
    }

    return ss.str();
}
