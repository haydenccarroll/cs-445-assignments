#include "Compound.hpp"
#include "../Decl/Decl.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Compound::Compound() : Stmt::Stmt() { m_stmtType = StmtType::Compound; }

Compound::Compound(unsigned linenum)
    : Stmt::Stmt(linenum, StmtType::Compound) {}

Compound::Compound(unsigned linenum, Node *localdecls, Node *stmtlist)
    : Stmt::Stmt(linenum, StmtType::Compound) {
    addChild(localdecls);
    addChild(stmtlist);
}

Decl::Decl *Compound::localdecls() const {
    return getChild(0)->cast<Decl::Decl *>();
}

Stmt *Compound::stmtlist() const { return getChild(1)->cast<Stmt *>(); }
} // namespace AST::Stmt