#include "../hpp/funDecl.hpp"

#include "../../node.hpp"
#include "../../../types.hpp"

#include <string>

FunDeclNode::FunDeclNode(unsigned int lineNum, std::string funcName, DataType returnType) :
ASTNode::ASTNode(lineNum),
m_funcName(funcName),
m_returnType(returnType)
{
}
