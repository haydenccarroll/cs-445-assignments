#pragma once

#include "../Exp.hpp"

#include <map>

namespace AST::Exp::Op {

class Op : public Exp {
  public:
    Op();
    Op(unsigned lineNum);
    Op(unsigned lineNum, OpType opType);
    
    const OpType &opType() const;

    virtual void deduceType() = 0;
    virtual bool is(OpType t) const override;

  protected:
    OpType m_opType;
};
} // namespace AST::Exp::Op