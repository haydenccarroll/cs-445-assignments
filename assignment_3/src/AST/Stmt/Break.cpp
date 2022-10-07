#include "Break.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Break::Break() : Stmt::Stmt() { m_stmtType = StmtType::Break; }

Break::Break(unsigned linenum) : Stmt::Stmt(linenum, StmtType::Break) {}
} // namespace AST::Stmt