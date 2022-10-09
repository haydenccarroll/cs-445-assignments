#pragma once

#include "../Node.h"

#include <map>
#include <string>

namespace Tree::Stmt {

// Base statement node
class Stmt : public Node {
  public:
    Stmt();
    // param lineNum - Line number the node appears on
    Stmt(unsigned lineNum);
    Stmt(unsigned lineNum, StmtType stmtType);

    const StmtType &stmtType() const;

    virtual std::string toString(bool debugging = false) const override;
    virtual bool is(StmtType) const override;

  protected:
    StmtType m_stmtType;
};
} // namespace Tree::Stmt