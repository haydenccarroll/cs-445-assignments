#pragma once

#include "../Exp/Exp.hpp"
#include "../Node.hpp"
#include "Decl.hpp"

#include <map>
#include <string>

namespace AST::Decl {
/// Variable declaration node
class Var : public Decl {
  public:
    Var();
    /// @param linenum Line number the node appears on
    Var(unsigned linenum);
    /// @param linenum Line number the node appears on
    /// @param id String identifier
    /// @param isArray Whether or not the variable is an array
    Var(unsigned linenum, const std::string &id, bool isArray);

    bool isInitialized() const;
    Exp::Exp *initValue();
    /// Set the variable and its siblings to static
    void setStatic();

    virtual std::string toString(bool debugging = false) const override;
};
} // namespace AST::Decl