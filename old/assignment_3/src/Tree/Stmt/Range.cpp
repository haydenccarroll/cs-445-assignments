#include "Range.h"
#include "../Exp/Exp.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
Range::Range() : Stmt::Stmt() { m_stmtType = StmtType::Range; }

Range::Range(unsigned lineNum) : Stmt::Stmt(lineNum, StmtType::Range) {}

Range::Range(unsigned lineNum, Node *from, Node *to, Node *by)
    : Stmt::Stmt(lineNum, StmtType::Range) {
    addChild(from);
    addChild(to);
    addChild(by);
}

Exp::Exp *Range::from() const { return getChild(0)->cast<Exp::Exp *>(); }

Exp::Exp *Range::to() const { return getChild(1)->cast<Exp::Exp *>(); }

Exp::Exp *Range::by() const { return getChild(2)->cast<Exp::Exp *>(); }
} // namespace Tree::Stmt