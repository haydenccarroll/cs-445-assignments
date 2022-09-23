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
        /// @param lineNum Line number the node appears on
        Return(unsigned lineNum);
        /// @param lineNum Line number the node appears on
        Return(unsigned lineNum, Node *exp);
    };
}