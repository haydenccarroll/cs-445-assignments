#pragma once

#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"
#include "Message.hpp"

#include <map>
#include <optional>
#include <string>
#include <vector>

class SemanticsChecker {
  public:
    SemanticsChecker();
    SemanticsChecker(bool debug);
    const SymbolTable &symbolTable() const;
    void analyze(AST::Node *);
    void print() const;
    int numErrors() const;
    int numWarnings() const;

  private:
    SymbolTable m_symbolTable;
    /// Mapping for errors and warning messages
    /// Maps from line number to bucket of messages
    std::map<unsigned, std::vector<Message>> m_messages;
    unsigned m_numErrors = 0;
    unsigned m_numWarnings = 0;
    std::optional<std::string> m_scopeName;
    bool m_mainIsDefined;
    bool m_analyzed = false;
    bool m_debug = false;
    AST::Decl::Parm *m_parms = nullptr;

    void enterScope();
    void enterScope(const std::optional<std::string> &);
    void leaveScope();

    void analyzeDefinitions(AST::Exp::Op::Asgn *);
    void analyzeTree(AST::Node *);
    void analyzeNode(AST::Decl::Decl *);
    void analyzeNode(AST::Exp::Exp *);
    void analyzeNode(AST::Exp::Op::Op *);
    void analyzeNode(AST::Exp::Op::Unary *);
    void analyzeNode(AST::Exp::Op::Asgn *);
    void analyzeNode(AST::Exp::Op::Bool *);
    void analyzeNode(AST::Stmt::Stmt *);
};