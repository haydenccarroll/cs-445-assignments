#include "Var.h"
#include "../Exp/Exp.h"
#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace Tree::Decl {
Var::Var() : Decl::Decl() { m_declType = DeclType::Var; }

Var::Var(unsigned lineNum) : Decl::Decl(lineNum, DeclType::Var) {}

Var::Var(unsigned lineNum, const std::string &id, bool isArray)
    : Decl::Decl(lineNum, DeclType::Var) {
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
    str += " of type " + Types::toString(m_typeInfo.type.value()) + lineTag();
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
} // namespace Tree::Decl