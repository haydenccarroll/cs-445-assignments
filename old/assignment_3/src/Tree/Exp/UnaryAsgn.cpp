#include "UnaryAsgn.h"
#include "../Node.h"
#include "Id.h"
#include "Unary.h"

#include <map>
#include <string>

namespace Tree::Exp::Op {
UnaryAsgn::UnaryAsgn() : Unary::Unary() { m_unaryOpType = UnaryOpType::Asgn; }

UnaryAsgn::UnaryAsgn(unsigned lineNum)
    : Unary::Unary(lineNum, UnaryOpType::Asgn) {}

UnaryAsgn::UnaryAsgn(unsigned lineNum, UnaryAsgnType opType, Node *exp)
    : Unary::Unary(lineNum, UnaryOpType::Asgn), m_unaryAsgnType(opType) {
    if (m_children.size() == 1 && getChild(0) == nullptr) {
        setChild(0, exp);
    } else {
        addChild(exp);
    }
}

UnaryAsgnType UnaryAsgn::unaryAsgnType() const { return m_unaryAsgnType; }

std::string UnaryAsgn::toString(bool debugging) const {
    std::string str = "Assign: " + Types::toString(m_unaryAsgnType);

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}

void UnaryAsgn::deduceType() {
    if (mutableExp() != nullptr) {
        m_typeInfo = mutableExp()->typeInfo();
    }
}

Exp *UnaryAsgn::mutableExp() const { return getChild(0)->cast<Exp *>(); }

bool UnaryAsgn::is(UnaryAsgnType t) const {
    return this != nullptr && m_unaryAsgnType == t;
}
} // namespace Tree::Exp::Op