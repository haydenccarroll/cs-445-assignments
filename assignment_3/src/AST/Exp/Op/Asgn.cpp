#include "Asgn.hpp"
#include "../../Node.hpp"
#include "../Exp.hpp"
#include "../Id.hpp"
#include "Binary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
Asgn::Asgn() : Binary::Binary() { m_binaryOpType = BinaryOpType::Asgn; }

Asgn::Asgn(unsigned linenum) : Binary::Binary(linenum, BinaryOpType::Asgn) {}

Asgn::Asgn(unsigned linenum, AsgnType asgnType, Node *exp1, Node *exp2)
    : Binary::Binary(linenum, BinaryOpType::Asgn), m_asgnType(asgnType) {
    addChild(exp1);
    addChild(exp2);
}

const AsgnType &Asgn::asgnType() const { return m_asgnType; }

std::string Asgn::toString(bool debugging) const {
    std::string str = "Assign: " + Types::toString(m_asgnType);

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}

void Asgn::deduceType() {
    if (mutableExp() != nullptr) {
        m_typeInfo = mutableExp()->typeInfo();
    }
}

Exp *Asgn::mutableExp() const { return getChild(0)->cast<Exp *>(); }

Exp *Asgn::exp() const { return getChild(1)->cast<Exp *>(); }

bool Asgn::is(AsgnType t) const { return this != nullptr && m_asgnType == t; }
} // namespace AST::Exp::Op