#pragma once

#include "Binary.hpp"

namespace AST::Exp::Op {

class Bool : public Binary {
  public:
    Bool();
    Bool(unsigned linenum);
    Bool(unsigned linenum, BoolOpType boolOpType);

    const BoolOpType &boolOpType() const;
    
    virtual std::string toString(bool debugging = false) const override;
    virtual bool is(BoolOpType) const override;

  protected:
    BoolOpType m_boolOpType;
};
} // namespace AST::Exp::Op::Bool