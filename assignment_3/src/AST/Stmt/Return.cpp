#include "Return.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Return::Return() : Stmt::Stmt() { m_stmtType = StmtType::Return; }

Return::Return(unsigned lineNum) : Stmt::Stmt(lineNum, StmtType::Return) {}

Return::Return(unsigned lineNum, Node *exp)
    : Stmt::Stmt(lineNum, StmtType::Return) {
    addChild(exp);
}

Exp::Exp *Return::exp() const { return getChild(0)->cast<Exp::Exp *>(); }
} // namespace AST::Stmt