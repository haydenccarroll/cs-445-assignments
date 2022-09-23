#pragma once

#include "../Node.h"

#include <string>

namespace AST::Exp
{
    /// Range node
    class Range : public Node
    {
    public:
        Range();
        /// @param lineNum Line number the node appears on
        Range(unsigned lineNum);
        /// @param lineNum Line number the node appears on
        /// @param from Beginning of range
        /// @param to End of range
        /// @param by Optional, amount to increment by
        Range(unsigned lineNum, Node *from, Node *to, Node *by = nullptr);
        virtual std::string toString() const override;
    };
}