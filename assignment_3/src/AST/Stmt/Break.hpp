#pragma once

#include "../Node.hpp"
#include "Stmt.hpp"

#include <string>

namespace AST::Stmt {
/// Break statement node
class Break : public Stmt {
  public:
    Break();
    /// @param linenum Line number the node appears on
    Break(unsigned linenum);
};
} // namespace AST::Stmt