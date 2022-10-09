#include "Decl.h"
#include "../Node.h"

#include <map>
#include <string>

namespace Tree::Decl {
Decl::Decl() : Node::Node() { m_nodeType = NodeType::Decl; }

Decl::Decl(unsigned lineNum) : Node::Node(lineNum, NodeType::Decl) {}

Decl::Decl(unsigned lineNum, DeclType declType)
    : Node::Node(lineNum, NodeType::Decl) {
    m_declType = declType;
}

void Decl::setType(DataType type) {
    m_typeInfo.type = type;
    if (m_sibling != nullptr) {
        ((Decl *)m_sibling)->setType(type);
    }
}

const DeclType &Decl::declType() const { return m_declType; }

const std::string &Decl::id() const { return m_id; }

SuperDataType &Decl::typeInfo() { return m_typeInfo; }

const SuperDataType &Decl::typeInfo() const { return m_typeInfo; }

std::string Decl::typeTag() const { return Types::toString(m_typeInfo); }

bool Decl::is(DeclType t) const { return this != nullptr && m_declType == t; }
} // namespace Tree::Decl