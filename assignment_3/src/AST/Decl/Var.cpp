#include "Var.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Var::Var() : Decl::Decl() { m_declType = DeclType::Var; }

Var::Var(unsigned linenum) : Decl::Decl(linenum, DeclType::Var) {}

Var::Var(unsigned linenum, const std::string &id, bool isArray)
    : Decl::Decl(linenum, DeclType::Var) {
    m_typeInfo.isArray = isArray;
    m_id = id;
}

void Var::setStatic() {
    if (m_sibling != nullptr) {
        ((Var *)m_sibling)->setStatic();
    }

    m_typeInfo.isStatic = true;
}

std::string Var::toString(bool debugging) const {
    std::string str = "Var: " + m_id;
    if (m_typeInfo.isArray) {
        str += " is array";
    }
    str += " of";
    if (m_typeInfo.isStatic) {
        str += " static";
    }
    str += " type " + Types::toString(m_typeInfo.type.value()) + lineTag();
    return str;
}

bool Var::isInitialized() const {
    return !m_children.empty() && m_children[0] != nullptr;
}

Exp::Exp *Var::initValue() {
    if (m_children.empty()) {
        return nullptr;
    } else {
        return (Exp::Exp *)m_children[0];
    }
}
} // namespace AST::Decl