#pragma once

#include "../../Node.hpp"
#include "../Exp.hpp"
#include "../Id.hpp"
#include "Unary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
/// Unary assignment operator
class UnaryAsgn : public Unary {
  public:
    /// Assignment type

    UnaryAsgn();
    /// @param lineNum Line number the node appears on
    UnaryAsgn(unsigned lineNum);
    /// @param lineNum Line number the node appears on
    /// @param opType Assignment type
    /// @param exp The node being assigned
    UnaryAsgn(unsigned lineNum, UnaryAsgnType opType, Node *exp);

    UnaryAsgnType unaryAsgnType() const;
    Exp *mutableExp() const;

    virtual std::string toString(bool debugging = false) const override;
    virtual void deduceType() override;
    virtual bool is(UnaryAsgnType) const override;

  protected:
    UnaryAsgnType m_unaryAsgnType;
};
} // namespace AST::Exp::Op