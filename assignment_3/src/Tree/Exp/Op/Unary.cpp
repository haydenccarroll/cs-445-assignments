#include "Unary.h"
#include "../../Node.h"
#include "../Exp.h"
#include "Op.h"

#include <map>
#include <string>
#include <stdexcept>


namespace Tree::Exp::Op {

Unary::Unary() : Op::Op() { m_opType = OpType::Unary; }

Unary::Unary(unsigned lineNum) : Op::Op(lineNum, OpType::Unary) {}

Unary::Unary(unsigned lineNum, UnaryOpType opType, Node *exp)
    : Op::Op(lineNum, OpType::Unary), m_unaryOpType(opType) {
    addChild(exp);
}

const UnaryOpType &Unary::unaryOpType() const { return m_unaryOpType; }

void Unary::addExp(Node *exp) {
    if (m_children.size() > 0) {
        if (getChild(0) == nullptr) {
            setChild(0, exp);
        } else {
            throw std::runtime_error(
                "Unary operator cannot have more than one child.");
        }
    } else {
        addChild(exp);
    }
}

Exp *Unary::operand() const {
    if (m_children.empty()) {
        throw std::runtime_error("Unary operator has no operand.");
    }

    return getChild(0)->cast<Exp *>();
}

std::string Unary::toString(bool debugging) const {
    std::string str = "Op: " + Types::toString(m_unaryOpType);

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}

void Unary::deduceType() {
    switch (m_unaryOpType) {
    case UnaryOpType::Asgn: {
        // never reaches here, because deduceType is overloaded by UnaryAsgn
        break;
    }
    case UnaryOpType::Chsign: {
        m_typeInfo.type = Type::Int;
        break;
    }
    case UnaryOpType::Not: {
        m_typeInfo.type = Type::Bool;
        break;
    }
    case UnaryOpType::Random: {
        m_typeInfo.type = Type::Int;
        break;
    }
    case UnaryOpType::Sizeof: {
        m_typeInfo.type = Type::Int;
        break;
    }
    }
}

bool Unary::is(UnaryOpType t) const { return this != nullptr && m_unaryOpType == t; }
} // namespace Tree::Exp::Op