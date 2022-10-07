#include "Decl.hpp"
#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Decl::Decl() : Node::Node() { m_nodeType = NodeType::Decl; }

Decl::Decl(unsigned linenum) : Node::Node(linenum, NodeType::Decl) {}

Decl::Decl(unsigned linenum, DeclType declType)
    : Node::Node(linenum, NodeType::Decl) {
    m_declType = declType;
}

void Decl::setType(Type type) {
    m_typeInfo.type = type;
    if (m_sibling != nullptr) {
        ((Decl *)m_sibling)->setType(type);
    }
}

const DeclType &Decl::declType() const { return m_declType; }

const std::string &Decl::id() const { return m_id; }

TypeInfo &Decl::typeInfo() { return m_typeInfo; }

const TypeInfo &Decl::typeInfo() const { return m_typeInfo; }

std::string Decl::typeTag() const { return Types::toString(m_typeInfo); }

bool Decl::is(DeclType t) const { return this != nullptr && m_declType == t; }
} // namespace AST::Decl