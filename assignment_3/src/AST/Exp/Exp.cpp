#include "Exp.hpp"

namespace AST::Exp {
Exp::Exp() : Node::Node() { m_nodeType = NodeType::Exp; }

Exp::Exp(unsigned linenum) : Node::Node(linenum, NodeType::Exp) {}

Exp::Exp(unsigned linenum, ExpType expType)
    : Node::Node(linenum, NodeType::Exp), m_expType(expType) {}

const ExpType &Exp::expType() const { return m_expType; }

void Exp::setType(TypeInfo typeInfo) { m_typeInfo = typeInfo; }

TypeInfo &Exp::typeInfo() { return m_typeInfo; }

const TypeInfo &Exp::typeInfo() const { return m_typeInfo; }

std::string Exp::typeTag() const { return Types::toString(m_typeInfo); }

bool Exp::is(ExpType t) const { return this != nullptr && m_expType == t; }
} // namespace AST::Exp