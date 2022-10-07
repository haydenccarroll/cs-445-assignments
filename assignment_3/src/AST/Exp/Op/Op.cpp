#include "Op.hpp"

namespace AST::Exp::Op {

Op::Op() : Exp::Exp() { m_expType = ExpType::Op; }

Op::Op(unsigned linenum) : Exp::Exp(linenum, ExpType::Op) {}

Op::Op(unsigned linenum, OpType opType)
    : Exp::Exp(linenum, ExpType::Op), m_opType(opType) {}

const OpType &Op::opType() const { return m_opType; }

bool Op::is(OpType t) const { return this != nullptr && m_opType == t; }
} // namespace AST::Exp::Op