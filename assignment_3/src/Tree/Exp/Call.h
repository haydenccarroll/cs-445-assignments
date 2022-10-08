#pragma once

#include "../Node.h"
#include "Exp.h"

#include <string>

namespace Tree::Exp {
/// Function call node
class Call : public Exp {
  public:
    Call();
    /// @param lineNum Line number the node appears on
    Call(unsigned lineNum);
    /// @param lineNum Line number the node appears on
    /// @param id String identifier of the function
    /// @param arglist Optional, argument list for function call
    Call(unsigned lineNum, const std::string &id, Node *arglist = nullptr);

    const std::string &id() const;
    Exp* arglist() const;

    virtual std::string toString(bool debugging = false) const override;

  protected:
    std::string m_id;
};
} // namespace Tree::Exp