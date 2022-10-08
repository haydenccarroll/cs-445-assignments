#pragma once

#include "../Tree/Tree.h"
#include "SymbolTable.h"
#include "Message.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

class Semantics {
  public:
    Semantics();
    Semantics(bool debug);
    const SymbolTable &symbolTable() const;
    void analyze(Tree::Node *);
    void print() const;
    int numErrors() const;
    int numWarnings() const;

  private:
    SymbolTable m_symbolTable;
    // Mapping for errors and warning messages
    // Maps from line number to bucket of messages
    std::map<unsigned, std::vector<Message>> m_messages;
    unsigned m_numErrors = 0;
    unsigned m_numWarnings = 0;
    std::optional<std::string> m_scopeName;
    bool m_mainIsDefined;
    bool m_analyzed = false;
    bool m_debug = false;
    Tree::Decl::Parm *m_parms = nullptr;

    void enterScope();
    void enterScope(const std::optional<std::string> &);
    void leaveScope();

    void analyzeDefinitions(Tree::Exp::Op::Asgn *);
    void analyzeTree(Tree::Node *);
    void analyzeNode(Tree::Decl::Decl *);
    void analyzeNode(Tree::Exp::Exp *);
    void analyzeNode(Tree::Exp::Op::Op *);
    void analyzeNode(Tree::Exp::Op::Unary *);
    void analyzeNode(Tree::Exp::Op::Asgn *);
    void analyzeNode(Tree::Exp::Op::Bool *);
    void analyzeNode(Tree::Stmt::Stmt *);
};