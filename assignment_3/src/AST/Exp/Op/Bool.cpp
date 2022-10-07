#include "Bool.hpp"

namespace AST::Exp::Op {
Bool::Bool() : Binary::Binary() {
    m_binaryOpType = BinaryOpType::Bool;
    m_typeInfo.type = Type::Bool;
}

Bool::Bool(unsigned linenum) : Binary::Binary(linenum, BinaryOpType::Bool) {
    m_typeInfo.type = Type::Bool;
}

Bool::Bool(unsigned linenum, BoolOpType boolOpType)
    : Binary::Binary(linenum, BinaryOpType::Bool), m_boolOpType(boolOpType) {
    m_typeInfo.type = Type::Bool;
}

std::string Bool::toString(bool debugging) const {
    std::string str = "Op: " + Types::toString(m_boolOpType);

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}

const BoolOpType &Bool::boolOpType() const { return m_boolOpType; }

bool Bool::is(BoolOpType t) const {
    return this != nullptr && m_boolOpType == t;
}
} // namespace AST::Exp::Op