#pragma once

#include "../Exp/Exp.h"
#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace Tree::Decl {
/// Variable declaration node
class Var : public Decl {
  public:
    Var();
    /// @param lineNum Line number the node appears on
    Var(unsigned lineNum);
    /// @param lineNum Line number the node appears on
    /// @param id String identifier
    /// @param isArray Whether or not the variable is an array
    Var(unsigned lineNum, const std::string &id, bool isArray);

    bool isInitialized() const;
    Exp::Exp *initValue();
    /// Set the variable and its siblings to static
    void setStatic();

    virtual std::string toString(bool debugging = false) const override;
};
} // namespace Tree::Decl