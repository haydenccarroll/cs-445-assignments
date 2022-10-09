#pragma once

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt {
// Break statement node
class Break : public Stmt {
  public:
    Break();
    // param lineNum - Line number the node appears on
    Break(unsigned lineNum);
};
} // namespace Tree::Stmt