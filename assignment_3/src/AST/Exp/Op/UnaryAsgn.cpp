#include "UnaryAsgn.hpp"
#include "../../Node.hpp"
#include "../Id.hpp"
#include "Unary.hpp"

#include <map>
#include <string>

namespace AST::Exp::Op {
UnaryAsgn::UnaryAsgn() : Unary::Unary() { m_unaryOpType = UnaryOpType::Asgn; }

UnaryAsgn::UnaryAsgn(unsigned linenum)
    : Unary::Unary(linenum, UnaryOpType::Asgn) {}

UnaryAsgn::UnaryAsgn(unsigned linenum, UnaryAsgnType opType, Node *exp)
    : Unary::Unary(linenum, UnaryOpType::Asgn), m_unaryAsgnType(opType) {
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
} // namespace AST::Exp::Op