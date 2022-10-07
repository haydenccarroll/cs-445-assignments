#pragma once

#include "../Decl/Decl.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
class Compound : public Stmt {
  public:
    Compound();
    /// @param linenum Line number the node appears on
    Compound(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param localdecls Local declarations, use nullptr if none
    /// @param stmtlist Statement list, use nullptr if none
    Compound(unsigned linenum, Node *localdecls, Node *stmtlist);
    /// @returns The local declarations
    Decl::Decl *localdecls() const;
    /// @returns The statement list
    Stmt *stmtlist() const;
};
} // namespace AST::Stmt