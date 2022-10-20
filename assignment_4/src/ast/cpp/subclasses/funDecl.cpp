#include "../../hpp/subclasses/funDecl.hpp"

#include "../../hpp/node.hpp"
#include "../../../types/include.hpp"

#include <string>
#include <sstream>
FunDeclNode::FunDeclNode(unsigned int lineNum, std::string funcName, DataType returnType) :
DeclNode::DeclNode(lineNum, funcName, returnType)
{
}

std::string FunDeclNode::toString(bool printType)
{
    std::stringstream ss;
    ss << "Func: " << m_name << " returns "
              << m_dataType.toString(false);
    return ss.str();
}
