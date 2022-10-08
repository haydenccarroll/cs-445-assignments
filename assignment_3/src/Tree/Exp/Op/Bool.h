#pragma once

#include "Binary.h"

namespace Tree::Exp::Op {

class Bool : public Binary {
  public:
    Bool();
    Bool(unsigned lineNum);
    Bool(unsigned lineNum, BoolOpType boolOpType);

    const BoolOpType &boolOpType() const;
    
    virtual std::string toString(bool debugging = false) const override;
    virtual bool is(BoolOpType) const override;

  protected:
    BoolOpType m_boolOpType;
};
} // namespace Tree::Exp::Op::Bool