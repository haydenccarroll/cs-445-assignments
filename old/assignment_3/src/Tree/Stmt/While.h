#pragma once

#include "../Exp/Exp.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
// While loop node
class While : public Stmt {
  public:
    While();
    // param lineNum - Line number the node appears on
    While(unsigned lineNum);
    // param lineNum - Line number the node appears on
    // param exp - Expression to evaluate to Boolean
    // param stmt - Loop body
    While(unsigned lineNum, Node *exp, Node *stmt);
    // returns Expression/condition to evaluate
    Exp::Exp *exp() const;
    // returns Statement to execute every loop
    Stmt *stmt() const;
};
} // namespace Tree::Stmt