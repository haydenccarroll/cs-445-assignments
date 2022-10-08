#include "Break.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
Break::Break() : Stmt::Stmt() { m_stmtType = StmtType::Break; }

Break::Break(unsigned lineNum) : Stmt::Stmt(lineNum, StmtType::Break) {}
} // namespace Tree::Stmt