#include "Func.hpp"
#include "../Node.hpp"
#include "../Stmt/Compound.hpp"
#include "Decl.hpp"
#include "Parm.hpp"

#include <map>
#include <string>

namespace AST::Decl {
Func::Func() : Decl::Decl() {
    m_declType = DeclType::Func;
    m_typeInfo.type = Type::Void;
}

Func::Func(unsigned linenum) : Decl::Decl(linenum, DeclType::Func) {
    m_typeInfo.type = Type::Void;
}

Func::Func(unsigned linenum, const std::string &id, Node *parms,
           Node *compoundstmt)
    : Decl::Decl(linenum, DeclType::Func) {
    m_typeInfo = {Type::Void, false, false};
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
    m_parms = (Parm *)parms;
    m_compoundStmt = (Stmt::Compound *)compoundstmt;
}

Func::Func(unsigned linenum, Type returnType, const std::string &id,
           Node *parms, Node *compoundstmt)
    : Decl::Decl(linenum) {
    m_typeInfo = {returnType, false, false};
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
    m_parms = (Parm *)parms;
    m_compoundStmt = (Stmt::Compound *)compoundstmt;
}

std::string Func::toString(bool debugging) const {
    return "Func: " + m_id + " returns type " +
           Types::toString(m_typeInfo.type) + lineTag();
}

bool Func::hasParms() const { return m_parms != nullptr; }

Parm *Func::parms() { return m_parms; }
} // namespace AST::Decl