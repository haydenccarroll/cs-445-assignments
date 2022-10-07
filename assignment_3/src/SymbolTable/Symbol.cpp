#include "Symbol.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

Symbol::Symbol() : m_decl(nullptr) {}

Symbol &Symbol::name(const std::string &name) {
    m_id = name;
    return *this;
}

Symbol &Symbol::declare(AST::Decl::Decl *decl) {
    if (decl != nullptr) {
        m_decl = decl;
    }
    return *this;
}

Symbol &Symbol::define(unsigned linenum) {
    if (!m_lineDefined.has_value()) {
        m_lineDefined = linenum;
    }
    return *this;
}

Symbol &Symbol::use(unsigned linenum) {
    if (!isDefined()) {
        m_linesUsedBeforeDefined.push_back(linenum);
    } else {
        m_linesUsedAfterDefined.push_back(linenum);
    }
    return *this;
}

bool Symbol::isDeclared() const { return m_decl != nullptr; }

bool Symbol::isDefined() const {
    return m_lineDefined.has_value() ||
           (isDeclared() && m_decl->declType() == AST::DeclType::Parm);
}

bool Symbol::isUsed() const {
    return !(m_linesUsedBeforeDefined.empty() &&
             m_linesUsedAfterDefined.empty());
}

bool Symbol::isIterator() const { return m_isIterator; }

void Symbol::setIterator(bool b) { m_isIterator = b; }

AST::Decl::Decl *Symbol::decl() const { return m_decl; }

std::vector<unsigned> Symbol::linesUsedBeforeDefined() const {
    std::vector<unsigned> linesused = m_linesUsedBeforeDefined;
    std::sort(linesused.begin(), linesused.end());

    return linesused;
}

const std::optional<unsigned> &Symbol::lineDefined() const {
    return m_lineDefined;
}