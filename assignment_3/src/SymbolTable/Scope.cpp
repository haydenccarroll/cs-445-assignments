#include "Scope.hpp"
#include "Symbol.hpp"

#include <iostream>
#include <map>
#include <string>

Scope::Scope() : m_id("global") {}

Scope::Scope(const std::string &id) : m_id(id) {}

bool Scope::contains(const std::string &id) const {
    bool result = m_symbols.find(id) != m_symbols.end();
    return result;
}

Symbol &Scope::getSymbol(const std::string &id) {
    if (!contains(id)) {
        m_symbols.insert({id, Symbol()});
        m_symbols.at(id).name(id);
    }
    return m_symbols.at(id);
}

std::map<std::string, Symbol> &Scope::getSymbols() { return m_symbols; }

std::string Scope::name() const { return m_id; }

void Scope::remove(const std::string &id) { m_symbols.erase(id); }