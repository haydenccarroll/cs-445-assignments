#include "Break.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
Break::Break() : Stmt::Stmt() { m_stmtType = StmtType::Break; }

Break::Break(unsigned lineNum) : Stmt::Stmt(lineNum, StmtType::Break) {}
} // namespace AST::Stmt