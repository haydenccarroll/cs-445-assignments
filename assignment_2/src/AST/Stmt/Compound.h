#pragma once

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class Compound : public Stmt
    {
    public:
        Compound();
        /// @param linenum Line number the node appears on
        Compound(unsigned linenum);
        /// @param linenum Line number the node appears on
        /// @param localdecls Local declarations, use nullptr if none
        /// @param stmtlist Statement list, use nullptr if none
        Compound(unsigned linenum, Node *localdecls, Node *stmtlist);
    };
}