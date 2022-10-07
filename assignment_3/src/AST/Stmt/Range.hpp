#pragma once

#include "../Exp/Exp.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
/// Range node
class Range : public Stmt {
  public:
    Range();
    /// @param linenum Line number the node appears on
    Range(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param from Beginning of range
    /// @param to End of range
    /// @param by Optional, amount to increment by
    Range(unsigned linenum, Node *from, Node *to, Node *by = nullptr);
    /// @returns The start of the range
    Exp::Exp *from() const;
    /// @returns The end of the range
    Exp::Exp *to() const;
    /// @returns The increment of the range
    Exp::Exp *by() const;
};
} // namespace AST::Stmt