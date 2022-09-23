#pragma once

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    /// Function call node
    class Call : public Stmt
    {
    public:
        Call();
        /// @param lineNum Line number the node appears on
        Call(unsigned lineNum);
        /// @param lineNum Line number the node appears on
        /// @param id String identifier of the function
        /// @param arglist Optional, argument list for function call
        Call(unsigned lineNum, const std::string &id, Node *arglist = nullptr);
        virtual std::string toString() const override;

    protected:
        std::string m_id;
    };
}