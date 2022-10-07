#pragma once

#include "../../Node.hpp"
#include "../Exp.hpp"
#include "../Id.hpp"
#include "Binary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
/// Assignment node
class Asgn : public Binary {
  public:
    /// Assignment types

    Asgn();
    /// @param linenum Line number the node appears on
    Asgn(unsigned linenum);
    /// Children nodes are optional in the constructor, but they must be
    /// provided eventually! Use addChildren to add them later.
    /// @param linenum Line number the node appears on
    /// @param type Assignment type
    /// @param exp1 The assignee
    /// @param exp2 The expression assigned to exp1
    Asgn(unsigned linenum, AsgnType asgnType, Node *exp1 = nullptr,
         Node *exp2 = nullptr);

    const AsgnType &asgnType() const;
    Exp *mutableExp() const;
    Exp *exp() const;

    virtual std::string toString(bool debugging = false) const override;
    virtual void deduceType() override;
    virtual bool is(AsgnType) const override;

  protected:
    AsgnType m_asgnType;
};
} // namespace AST::Exp::Op