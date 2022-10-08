#pragma once

#include "../../Node.h"
#include "../Exp.h"
#include "../Id.h"
#include "Binary.h"

#include <map>
#include <string>

namespace Tree::Exp::Op {
// Assignment node
class Asgn : public Binary {
  public:
    // Assignment types

    Asgn();
    // param lineNum - Line number the node appears on
    Asgn(unsigned lineNum);
    // Children nodes are optional in the constructor, but they must be
    // provided eventually! Use addChildren to add them later.
    // param lineNum - Line number the node appears on
    // param type - Assignment type
    // param exp1 - The assignee
    // param exp2 - The expression assigned to exp1
    Asgn(unsigned lineNum, AsgnType asgnType, Node *exp1 = nullptr,
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
} // namespace Tree::Exp::Op