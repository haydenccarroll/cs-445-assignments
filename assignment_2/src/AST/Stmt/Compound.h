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
        /// @param lineNum Line number the node appears on
        Compound(unsigned lineNum);
        /// @param lineNum Line number the node appears on
        /// @param localdecls Local declarations, use nullptr if none
        /// @param stmtlist Statement list, use nullptr if none
        Compound(unsigned lineNum, Node *localdecls, Node *stmtlist);
    };
}