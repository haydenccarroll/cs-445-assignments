#include "Id.hpp"
#include "../Node.hpp"
#include "Exp.hpp"

#include <string>

namespace AST::Exp {
Id::Id() : Exp::Exp() { m_expType = ExpType::Id; }

Id::Id(unsigned lineNum) : Exp::Exp(lineNum, ExpType::Id) {}

Id::Id(unsigned lineNum, const std::string &id)
    : Exp::Exp(lineNum, ExpType::Id), m_id(id) {}

const std::string &Id::id() const { return m_id; }

std::string Id::toString(bool debugging) const {
    std::string str = "Id: " + m_id;

    if (debugging) {
        str += typeTag();
    }

    str += lineTag();
    return str;
}
} // namespace AST::Exp