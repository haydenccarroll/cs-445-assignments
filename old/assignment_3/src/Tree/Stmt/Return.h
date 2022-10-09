#pragma once

#include "../Exp/Exp.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
// Function return statement node
class Return : public Stmt {
  public:
    Return();
    // param lineNum - Line number the node appears on
    Return(unsigned lineNum);
    // param lineNum - Line number the node appears on
    Return(unsigned lineNum, Node *exp);
    // returns Value to return
    Exp::Exp *exp() const;
};
} // namespace Tree::Stmt