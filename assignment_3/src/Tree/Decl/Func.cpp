#include "Func.h"
#include "../Node.h"
#include "../Stmt/Compound.h"
#include "Decl.h"
#include "Parm.h"

#include <map>
#include <string>

namespace Tree::Decl {
Func::Func() : Decl::Decl() {
    m_declType = DeclType::Func;
    m_typeInfo.type = DataType::Void;
}

Func::Func(unsigned lineNum) : Decl::Decl(lineNum, DeclType::Func) {
    m_typeInfo.type = DataType::Void;
}

Func::Func(unsigned lineNum, const std::string &id, Node *parms,
           Node *compoundstmt)
    : Decl::Decl(lineNum, DeclType::Func) {
    m_typeInfo = {DataType::Void, false, false};
    m_id = id;
    addChild(parms);
    addChild(compoundstmt);
    m_parms = (Parm *)parms;
    m_compoundStmt = (Stmt::Compound *)compoundstmt;
}

Func::Func(unsigned lineNum, DataType returnType, const std::string &id,
           Node *parms, Node *compoundstmt)
    : Decl::Decl(lineNum) {
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
} // namespace Tree::Decl