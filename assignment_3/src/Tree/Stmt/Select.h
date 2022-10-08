#pragma once

#include "../Exp/Exp.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
/// Select/If statement node
class Select : public Stmt {
  public:
    Select();
    /// @param lineNum Line number the node appears on
    Select(unsigned lineNum);
    /// @param lineNum Line number the node appears on
    /// @param exp Expression evaluated
    /// @param stmt1 Statement executed if exp is evaluated to true
    /// @param stmt2 Optional, statement executed if exp is evaluated to false
    /// (else part)
    Select(unsigned lineNum, Node *exp, Node *stmt1, Node *stmt2 = nullptr);
    /// @returns Expression/condition to evaluate
    Exp::Exp *exp() const;
    /// @returns Statement to execute if true
    Stmt *stmt1() const;
    /// @returns Statement to execute if false
    Stmt *stmt2() const;
};
} // namespace Tree::Stmt