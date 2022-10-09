#include "Select.h"
#include "../Exp/Exp.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
Select::Select() : Stmt::Stmt() { m_stmtType = StmtType::Select; }

Select::Select(unsigned lineNum) : Stmt::Stmt(lineNum, StmtType::Select) {}

Select::Select(unsigned lineNum, Node *exp, Node *stmt1, Node *stmt2)
    : Stmt::Stmt(lineNum, StmtType::Select) {
    addChild(exp);
    addChild(stmt1);
    addChild(stmt2);
}

Exp::Exp *Select::exp() const { return getChild(0)->cast<Exp::Exp *>(); }

Stmt *Select::stmt1() const { return getChild(1)->cast<Stmt *>(); };

Stmt *Select::stmt2() const { return getChild(2)->cast<Stmt *>(); };
} // namespace Tree::Stmt