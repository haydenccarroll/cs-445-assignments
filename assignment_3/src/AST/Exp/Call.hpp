#pragma once

#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
/// Function call node
class Call : public Exp {
  public:
    Call();
    /// @param linenum Line number the node appears on
    Call(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param id String identifier of the function
    /// @param arglist Optional, argument list for function call
    Call(unsigned linenum, const std::string &id, Node *arglist = nullptr);

    const std::string &id() const;
    Exp* arglist() const;

    virtual std::string toString(bool debugging = false) const override;

  protected:
    std::string m_id;
};
} // namespace AST::Exp