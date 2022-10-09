#include "Compound.h"
#include "../Decl/Decl.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
Compound::Compound() : Stmt::Stmt() { m_stmtType = StmtType::Compound; }

Compound::Compound(unsigned lineNum)
    : Stmt::Stmt(lineNum, StmtType::Compound) {}

Compound::Compound(unsigned lineNum, Node *localdecls, Node *stmtlist)
    : Stmt::Stmt(lineNum, StmtType::Compound) {
    addChild(localdecls);
    addChild(stmtlist);
}

Decl::Decl *Compound::localdecls() const {
    return getChild(0)->cast<Decl::Decl *>();
}

Stmt *Compound::stmtlist() const { return getChild(1)->cast<Stmt *>(); }
} // namespace Tree::Stmt