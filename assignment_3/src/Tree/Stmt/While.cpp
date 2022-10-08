#include "While.h"
#include "../Exp/Exp.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
While::While() : Stmt::Stmt() { m_stmtType = StmtType::While; }

While::While(unsigned lineNum) : Stmt::Stmt(lineNum, StmtType::While) {}

While::While(unsigned lineNum, Node *exp, Node *stmt)
    : Stmt::Stmt(lineNum, StmtType::While) {
    addChild(exp);
    addChild(stmt);
}

Exp::Exp *While::exp() const { return getChild(0)->cast<Exp::Exp *>(); }

Stmt *While::stmt() const { return getChild(1)->cast<Stmt *>(); }
} // namespace Tree::Stmt