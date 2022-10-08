#include "Return.h"
#include "../Exp/Exp.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
Return::Return() : Stmt::Stmt() { m_stmtType = StmtType::Return; }

Return::Return(unsigned lineNum) : Stmt::Stmt(lineNum, StmtType::Return) {}

Return::Return(unsigned lineNum, Node *exp)
    : Stmt::Stmt(lineNum, StmtType::Return) {
    addChild(exp);
}

Exp::Exp *Return::exp() const { return getChild(0)->cast<Exp::Exp *>(); }
} // namespace Tree::Stmt