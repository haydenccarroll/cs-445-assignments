#pragma once

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    /// Select/If statement node
    class Select : public Stmt
    {
    public:
        Select();
        /// @param linenum Line number the node appears on
        Select(unsigned linenum);
        /// @param linenum Line number the node appears on
        /// @param exp Expression evaluated
        /// @param stmt1 Statement executed if exp is evaluated to true
        /// @param stmt2 Optional, statement executed if exp is evaluated to false (else part)
        Select(unsigned linenum, Node *exp, Node *stmt1, Node *stmt2 = nullptr);
    };
}