#include "Parm.hpp"
#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Parm::Parm() : Decl::Decl() { m_declType = DeclType::Parm; }

Parm::Parm(unsigned linenum) : Decl::Decl(linenum, DeclType::Parm) {}

Parm::Parm(unsigned linenum, const std::string &id, bool isArray)
    : Decl::Decl(linenum, DeclType::Parm) {
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
} // namespace AST::Decl