#pragma once

#include "../Tree/Tree.h"
#include "SymbolTable.h"

#include <map>
#include <optional>
#include <string>
#include <vector>

class Msg {
  public:
    enum class MsgType { Error, Warning };
    Msg(MsgType type, const std::string &content);

    MsgType type() const;
    std::string content() const;

    static unsigned numWarnings();
    static unsigned numErrors();

  private:
    static unsigned s_numerrors;
    static unsigned s_numwarnings;

    MsgType m_type;
    std::string m_content;
};

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
    std::map<unsigned, std::vector<Msg>> m_messages;
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
