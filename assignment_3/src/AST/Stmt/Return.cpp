#include "Return.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Return::Return() : Stmt::Stmt() { m_stmtType = StmtType::Return; }

Return::Return(unsigned linenum) : Stmt::Stmt(linenum, StmtType::Return) {}

Return::Return(unsigned linenum, Node *exp)
    : Stmt::Stmt(linenum, StmtType::Return) {
    addChild(exp);
}

Exp::Exp *Return::exp() const { return getChild(0)->cast<Exp::Exp *>(); }
} // namespace AST::Stmt