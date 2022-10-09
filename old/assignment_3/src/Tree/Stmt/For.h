#pragma once

#include "../Exp/Id.h"
#include "../Node.h"
#include "Range.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
// For loop node
class For : public Stmt {
  public:
    For();
    // param lineNum - Line number the node appears on
    For(unsigned lineNum);
    // param lineNum - Line number the node appears on
    // param id - Iterator variable identifier
    // param range - Iteration range
    // param stmt - Loop body
    For(unsigned lineNum, Node *id, Node *range, Node *stmt);
    // returns The identifier of the iterator
    Exp::Id *id() const;
    // returns The range of the for loop
    Range *range() const;
    // returns The statement to execute every loop
    Stmt *stmt() const;
};
} // namespace Tree::Stmt