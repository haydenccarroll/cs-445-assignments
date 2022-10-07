#pragma once

#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
/// While loop node
class While : public Stmt {
  public:
    While();
    /// @param linenum Line number the node appears on
    While(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param exp Expression to evaluate to Boolean
    /// @param stmt Loop body
    While(unsigned linenum, Node *exp, Node *stmt);
    /// @returns Expression/condition to evaluate
    Exp::Exp *exp() const;
    /// @returns Statement to execute every loop
    Stmt *stmt() const;
};
} // namespace AST::Stmt