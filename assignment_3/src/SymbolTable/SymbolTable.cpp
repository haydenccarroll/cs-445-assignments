#include "SymbolTable.hpp"
#include "../AST/AST.hpp"
#include "Scope.hpp"
#include "Symbol.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

SymbolTable::SymbolTable() { enter("global"); }

SymbolTable::SymbolTable(bool debug) : m_debug(debug) { enter("global"); }

int SymbolTable::depth() const { return m_scopes.size(); }

void SymbolTable::enter(const std::string &id) {
    m_scopes.push_back(Scope(id));

    if (m_debug) {
        std::cout << "DEBUG(SymbolTable): enter scope \"" << scopeString()
                  << "\"." << std::endl;
    }
}

void SymbolTable::leave() {

    if (m_debug) {
        std::cout << "DEBUG(SymbolTable): leave scope \"" << scopeString()
                  << "\"." << std::endl;
    }

    if (m_scopes.size() == 1) {
        std::cout << "ERROR(SymbolTable): You cannot leave global scope.  "
                     "Number of scopes: "
                  << m_scopes.size() << "." << std::endl;
    } else {
        m_scopes.pop_back();
    }
}

void SymbolTable::declare(const std::string &id, AST::Decl::Decl *node) {

    auto *decl = (AST::Decl::Decl *)node;

    m_scopes.back().getSymbol(id).declare(node);

    if (m_debug) {
        std::cout << "DEBUG(SymbolTable): declared symbol " << id
                  << " in scope " << scopeString() << std::endl;
    }
}

bool SymbolTable::contains(const std::string &id) const {
    return std::any_of(m_scopes.begin(), m_scopes.end(),
                       [id](const Scope &scope) { return scope.contains(id); });
}

bool SymbolTable::containsImmediately(const std::string &id) const {
    return m_scopes.back().contains(id);
}

std::map<std::string, Symbol> &SymbolTable::getImmediateSymbols() {
    return m_scopes.back().getSymbols();
}

bool SymbolTable::isGlobal(const std::string &id) const {
    for (int i = m_scopes.size(); i > 0; i--) {
        if (m_scopes[i].contains(id)) {
            return false;
        }
    }

    return m_scopes.front().contains(id);
}

Symbol &SymbolTable::getSymbol(const std::string &id) {

    if (m_debug) {
        std::cout << "DEBUG(SymbolTable): lookup the symbol \"" << id
                  << "\" and ";
    }

    for (int i = m_scopes.size() - 1; i >= 0; i--) {
        if (m_scopes[i].contains(id)) {
            if (m_debug) {
                std::cout << "found it in the scope named \"" << scopeString()
                          << "\"." << std::endl;
            }
            return m_scopes[i].getSymbol(id);
        }
    }

    if (m_debug) {
        std::cout << "did NOT find it!" << std::endl;
    }
    // this creates a new symbol!
    // means it isn't declared yet
    return m_scopes.back().getSymbol(id);
}

Symbol &SymbolTable::operator[](const std::string &id) { return getSymbol(id); }

void SymbolTable::remove(const std::string &id) {
    for (int i = m_scopes.size() - 1; i >= 0; i--) {
        if (m_scopes[i].contains(id)) {
            m_scopes[i].remove(id);
            return;
        }
    }
}

void SymbolTable::removeImmediately(const std::string &id) {
    if (m_scopes.back().contains(id)) {
        m_scopes.back().remove(id);
    }
}

std::string SymbolTable::scopeString() const {
    std::string str;
    for (const auto &scope : m_scopes) {
        str += scope.name() + "::";
    }
    if (!str.empty()) {
        str = str.substr(0, str.length() - 2);
    }
    return str;
}