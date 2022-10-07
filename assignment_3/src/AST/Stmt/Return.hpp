#pragma once

#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
/// Function return statement node
class Return : public Stmt {
  public:
    Return();
    /// @param lineNum Line number the node appears on
    Return(unsigned lineNum);
    /// @param lineNum Line number the node appears on
    Return(unsigned lineNum, Node *exp);
    /// @returns Value to return
    Exp::Exp *exp() const;
};
} // namespace AST::Stmt