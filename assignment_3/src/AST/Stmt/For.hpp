#pragma once

#include "../Exp/Id.hpp"
#include "../Node.hpp"
#include "Range.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
/// For loop node
class For : public Stmt {
  public:
    For();
    /// @param linenum Line number the node appears on
    For(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param id Iterator variable identifier
    /// @param range Iteration range
    /// @param stmt Loop body
    For(unsigned linenum, Node *id, Node *range, Node *stmt);
    /// @returns The identifier of the iterator
    Exp::Id *id() const;
    /// @returns The range of the for loop
    Range *range() const;
    /// @returns The statement to execute every loop
    Stmt *stmt() const;
};
} // namespace AST::Stmt