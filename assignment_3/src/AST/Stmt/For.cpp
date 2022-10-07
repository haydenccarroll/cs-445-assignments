#include "For.hpp"
#include "../Exp/Id.hpp"
#include "../Node.hpp"
#include "Range.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
For::For() : Stmt::Stmt() { m_stmtType = StmtType::For; }

For::For(unsigned linenum) : Stmt::Stmt(linenum, StmtType::For) {}

For::For(unsigned linenum, Node *id, Node *range, Node *stmt)
    : Stmt::Stmt(linenum, StmtType::For) {
    addChild(id);
    addChild(range);
    addChild(stmt);
}

Exp::Id *For::id() const { return getChild(0)->cast<Exp::Id *>(); }

Range *For::range() const { return getChild(1)->cast<Range *>(); }

Stmt *For::stmt() const { return getChild(2)->cast<Stmt *>(); }

} // namespace AST::Stmt