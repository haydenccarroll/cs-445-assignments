#pragma once

#include "../Tree/Tree.h"

#include <optional>
#include <set>
#include <string>
#include <vector>

class Symbol {
  public:
    Symbol();
    Symbol &name(const std::string &);
    Symbol &declare(Tree::Decl::Decl *decl);
    Symbol &define(unsigned lineNum);
    Symbol &use(unsigned lineNum);
    bool isDeclared() const;
    bool isDefined() const;
    bool isUsed() const;
    bool isIterator() const;
    void setIterator(bool);
    Tree::Decl::Decl *decl() const;
    std::vector<unsigned> linesUsedBeforeDefined() const;
    const std::optional<unsigned> &lineDefined() const;

  private:
    std::string m_id;
    Tree::Decl::Decl *m_decl = nullptr;
    std::vector<unsigned> m_linesUsedBeforeDefined;
    std::vector<unsigned> m_linesUsedAfterDefined;
    std::optional<unsigned> m_lineDefined;
    bool m_isIterator = false;
};