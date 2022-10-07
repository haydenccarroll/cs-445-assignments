#pragma once

#include "../../Node.hpp"
#include "../Exp.hpp"
#include "Op.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
/// Generic class for unary operator nodes
/// "Generic" as in one-size-fits-all, not using generics or templates.
class Unary : public Op {
  public:
    /// Unary operators

    Unary();
    /// @param linenum
    Unary(unsigned linenum);
    /// exp is optional in this constructor, but must be provided eventually!
    /// Set later with addExp.
    /// @param linenum
    /// @param opType Unary operator type
    /// @param exp Optional child expression
    Unary(unsigned linenum, UnaryOpType opType, Node *exp = nullptr);

    const UnaryOpType &unaryOpType() const;
    /// @param exp Child node
    void addExp(Node *exp);
    Exp *operand() const;

    virtual std::string toString(bool debugging = false) const override;
    virtual void deduceType() override;
    virtual bool is(UnaryOpType) const override;

  protected:
    UnaryOpType m_unaryOpType;
};
} // namespace AST::Exp::Op