#pragma once

#include "../Tree/Tree.h"
#include "Scope.h"
#include "Symbol.h"

#include <string>
#include <vector>

// // // // // // // // // // // // // // // // // // // //
//
// Introduction
//
// This symbol table library supplies basic insert and lookup for
// symbols linked to void * pointers of data.
//
// Plenty of room for improvement inlcuding: better debugging setup,
// passing of refs rather than values and purpose built char *
// routines, and C support.
//
// WARNING: lookup will return NULL pointer if key is not in table.
// This means the void * cannot have zero as a legal value! Attempting
// to save a NULL pointer will get a error.
//
// A main() is commented out and has testing code in it.
//
// Robert Heckendorn   Apr 3, 2021
// edited 10/8/2022
//


// // // // // // // // // // // // // // // // // // // //
//
// Class: SymbolTable
//
// Is a stack of scopes.   The global scope is created when the table is
// is constructed and remains for the lifetime of the object instance.
// SymbolTable manages nested scopes as a result.
//


class SymbolTable {
  public:
    SymbolTable();
    SymbolTable(bool debug);
    int depth() const;
    void enter(const std::string &name = "unnamed scope");
    void leave();
    void declare(const std::string &id, Tree::Decl::Decl *);
    bool contains(const std::string &) const;
    bool containsImmediately(const std::string &) const;
    bool isGlobal(const std::string &) const;
    void remove(const std::string &);
    void removeImmediately(const std::string &);
    std::map<std::string, Symbol> &getImmediateSymbols();
    Symbol &getSymbol(const std::string &);
    Symbol &operator[](const std::string &);

  private:
    std::vector<Scope> m_scopes;
    bool m_debug = false;

    std::string scopeString() const;
};
