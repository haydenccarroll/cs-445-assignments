#pragma once

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    /// While loop node
    class While : public Stmt
    {
    public:
        While();
        /// @param linenum Line number the node appears on
        While(unsigned linenum);
        /// @param linenum Line number the node appears on
        /// @param exp Expression to evaluate to Boolean
        /// @param stmt Loop body
        While(unsigned linenum, Node *exp, Node *stmt);
    };
}