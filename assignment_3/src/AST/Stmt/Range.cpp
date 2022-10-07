#include "Range.hpp"
#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Range::Range() : Stmt::Stmt() { m_stmtType = StmtType::Range; }

Range::Range(unsigned linenum) : Stmt::Stmt(linenum, StmtType::Range) {}

Range::Range(unsigned linenum, Node *from, Node *to, Node *by)
    : Stmt::Stmt(linenum, StmtType::Range) {
    addChild(from);
    addChild(to);
    addChild(by);
}

Exp::Exp *Range::from() const { return getChild(0)->cast<Exp::Exp *>(); }

Exp::Exp *Range::to() const { return getChild(1)->cast<Exp::Exp *>(); }

Exp::Exp *Range::by() const { return getChild(2)->cast<Exp::Exp *>(); }
} // namespace AST::Stmt