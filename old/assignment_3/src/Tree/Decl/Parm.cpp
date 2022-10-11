#include "Parm.h"
#include "../Node.h"

#include <map>
#include <string>

namespace Tree::Decl {
Parm::Parm() : Decl::Decl() { m_declType = DeclType::Parm; }

Parm::Parm(unsigned lineNum) : Decl::Decl(lineNum, DeclType::Parm) {}

Parm::Parm(unsigned lineNum, const std::string &id, bool isArray)
    : Decl::Decl(lineNum, DeclType::Parm) {
    m_typeInfo.isArray = isArray;
    m_id = id;
}

std::string Parm::toString(bool debugging) const {
    std::string str = "Parm: " + m_id;
    if (m_typeInfo.isArray) {
        str += " is array";
    }
    str += " of type " + Types::toString(m_typeInfo.type.value()) + lineTag();
    return str;
}
} // namespace Tree::Decl