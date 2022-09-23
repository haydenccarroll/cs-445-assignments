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
        /// @param lineNum Line number the node appears on
        While(unsigned lineNum);
        /// @param lineNum Line number the node appears on
        /// @param exp Expression to evaluate to Boolean
        /// @param stmt Loop body
        While(unsigned lineNum, Node *exp, Node *stmt);
    };
}