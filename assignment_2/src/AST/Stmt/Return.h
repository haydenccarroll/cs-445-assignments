#pragma once

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    /// Function return statement node
    class Return : public Stmt
    {
    public:
        Return();
        /// @param linenum Line number the node appears on
        Return(unsigned linenum);
        /// @param linenum Line number the node appears on
        Return(unsigned linenum, Node *exp);
    };
}