#include "Exp.h"

namespace Tree::Exp {
Exp::Exp() : Node::Node() { m_nodeType = NodeType::Exp; }

Exp::Exp(unsigned lineNum) : Node::Node(lineNum, NodeType::Exp) {}

Exp::Exp(unsigned lineNum, ExpType expType)
    : Node::Node(lineNum, NodeType::Exp), m_expType(expType) {}

const ExpType &Exp::expType() const { return m_expType; }

void Exp::setType(SuperDataType typeInfo) { m_typeInfo = typeInfo; }

SuperDataType &Exp::typeInfo() { return m_typeInfo; }

const SuperDataType &Exp::typeInfo() const { return m_typeInfo; }

std::string Exp::typeTag() const { return Types::toString(m_typeInfo); }

bool Exp::is(ExpType t) const { return this != nullptr && m_expType == t; }
} // namespace Tree::Exp