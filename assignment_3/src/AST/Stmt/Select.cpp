#include "Select.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Select::Select() : Stmt::Stmt() { m_stmtType = StmtType::Select; }

Select::Select(unsigned linenum) : Stmt::Stmt(linenum, StmtType::Select) {}

Select::Select(unsigned linenum, Node *exp, Node *stmt1, Node *stmt2)
    : Stmt::Stmt(linenum, StmtType::Select) {
    addChild(exp);
    addChild(stmt1);
    addChild(stmt2);
}

Exp::Exp *Select::exp() const { return getChild(0)->cast<Exp::Exp *>(); }

Stmt *Select::stmt1() const { return getChild(1)->cast<Stmt *>(); };

Stmt *Select::stmt2() const { return getChild(2)->cast<Stmt *>(); };
} // namespace AST::Stmt