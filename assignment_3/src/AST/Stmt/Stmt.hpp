#pragma once

#include "../Node.hpp"

#include <map>
#include <string>

namespace AST::Stmt {

/// Base statement node
class Stmt : public Node {
  public:
    Stmt();
    /// @param linenum Line number the node appears on
    Stmt(unsigned linenum);
    Stmt(unsigned linenum, StmtType stmtType);

    const StmtType &stmtType() const;

    virtual std::string toString(bool debugging = false) const override;
    virtual bool is(StmtType) const override;

  protected:
    StmtType m_stmtType;
};
} // namespace AST::Stmt