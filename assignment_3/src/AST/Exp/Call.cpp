#include "Call.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
Call::Call() : Exp::Exp() { m_expType = ExpType::Call; }

Call::Call(unsigned linenum) : Exp::Exp(linenum, ExpType::Call) {}

Call::Call(unsigned linenum, const std::string &id, Node *arglist)
    : Exp::Exp(linenum, ExpType::Call), m_id(id) {
    addChild(arglist);
}

const std::string &Call::id() const { return m_id; }

std::string Call::toString(bool debugging) const {
    std::string str = "Call: " + m_id;

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}

Exp *Call::arglist() const { return getChild(0)->cast<Exp *>(); }
} // namespace AST::Exp