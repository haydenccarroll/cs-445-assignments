#pragma once

#include "../Decl/Decl.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
class Compound : public Stmt {
  public:
    Compound();
    // param lineNum - Line number the node appears on
    Compound(unsigned lineNum);
    // param lineNum - Line number the node appears on
    // param localdecls - Local declarations, use nullptr if none
    // param stmtlist - Statement list, use nullptr if none
    Compound(unsigned lineNum, Node *localdecls, Node *stmtlist);
    // returns The local declarations
    Decl::Decl *localdecls() const;
    // returns The statement list
    Stmt *stmtlist() const;
};
} // namespace Tree::Stmt