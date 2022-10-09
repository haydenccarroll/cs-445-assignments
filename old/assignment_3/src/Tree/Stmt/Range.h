#pragma once

#include "../Exp/Exp.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
// Range node
class Range : public Stmt {
  public:
    Range();
    // param lineNum - Line number the node appears on
    Range(unsigned lineNum);
    // param lineNum - Line number the node appears on
    // param from - Beginning of range
    // param to - End of range
    // param by - Optional, amount to increment by
    Range(unsigned lineNum, Node *from, Node *to, Node *by = nullptr);
    // returns The start of the range
    Exp::Exp *from() const;
    // returns The end of the range
    Exp::Exp *to() const;
    // returns The increment of the range
    Exp::Exp *by() const;
};
} // namespace Tree::Stmt