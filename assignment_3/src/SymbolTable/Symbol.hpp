#pragma once

#include "../AST/AST.hpp"

#include <optional>
#include <set>
#include <string>
#include <vector>

class Symbol {
  public:
    Symbol();
    Symbol &name(const std::string &);
    Symbol &declare(AST::Decl::Decl *decl);
    Symbol &define(unsigned linenum);
    Symbol &use(unsigned linenum);
    bool isDeclared() const;
    bool isDefined() const;
    bool isUsed() const;
    bool isIterator() const;
    void setIterator(bool);
    AST::Decl::Decl *decl() const;
    std::vector<unsigned> linesUsedBeforeDefined() const;
    const std::optional<unsigned> &lineDefined() const;

  private:
    std::string m_id;
    AST::Decl::Decl *m_decl = nullptr;
    std::vector<unsigned> m_linesUsedBeforeDefined;
    std::vector<unsigned> m_linesUsedAfterDefined;
    std::optional<unsigned> m_lineDefined;
    bool m_isIterator = false;
};