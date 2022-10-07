#pragma once

#include "../AST/AST.hpp"
#include "Symbol.hpp"

#include <string>
#include <vector>

class Scope {
  public:
    Scope();
    Scope(const std::string &);
    bool contains(const std::string &) const;
    Symbol &getSymbol(const std::string &);
    std::map<std::string, Symbol> &getSymbols();
    std::string name() const;
    void remove(const std::string &);

  private:
    std::string m_id;
    std::map<std::string, Symbol> m_symbols;
};