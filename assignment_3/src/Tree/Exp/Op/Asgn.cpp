#include "Asgn.h"
#include "../../Node.h"
#include "../Exp.h"
#include "../Id.h"
#include "Binary.h"

#include <map>
#include <string>

namespace Tree::Exp::Op {
Asgn::Asgn() : Binary::Binary() { m_binaryOpType = BinaryOpType::Asgn; }

Asgn::Asgn(unsigned lineNum) : Binary::Binary(lineNum, BinaryOpType::Asgn) {}

Asgn::Asgn(unsigned lineNum, AsgnType asgnType, Node *exp1, Node *exp2)
    : Binary::Binary(lineNum, BinaryOpType::Asgn), m_asgnType(asgnType) {
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
} // namespace Tree::Exp::Op