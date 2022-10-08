#pragma once

#include "../Node.h"
#include "Exp.h"
#include "Op.h"

#include <map>
#include <string>

namespace Tree::Exp::Op {
// Generic class for binary operator nodes
// "Generic" as in one-size-fits-all, not using generics or templates.
class Binary : public Op {
  public:
    // Binary operators

    Binary();
    // param lineNum - Line number the node appears on
    Binary(unsigned lineNum);
    // exp1 and exp2 are optional arguments, but they must be set later if not
    // provided in the constructor! Set them with addChildren
    // param lineNum - Line number the node appears on
    // param opType - Operator type
    // param exp1 - First argument
    // param exp2 - Second argument
    Binary(unsigned lineNum, BinaryOpType opType, Node *exp1 = nullptr,
           Node *exp2 = nullptr);

    const BinaryOpType &binaryOpType() const;
    Exp *exp1() const;
    Exp *exp2() const;

    // param exp1 - First argument
    // param exp2 - Second argument
    virtual void addChildren(Node *exp1, Node *exp2);
    virtual std::string toString(bool debugging = false) const override;
    virtual void deduceType() override;
    virtual bool is(BinaryOpType) const override;

  protected:
    BinaryOpType m_binaryOpType;
};
} // namespace Tree::Exp::Op