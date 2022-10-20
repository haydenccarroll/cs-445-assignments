#pragma once

#include "../../ast/include.hpp"
#include "../../symTable/include.hpp"

class SemanticAnalyzer
{
public:
    SemanticAnalyzer(ASTNode* root, SymbolTable* symTable);
    void analyze();
private:
    ASTNode* m_root;
    SymbolTable* m_symTable;
    bool m_isMainDefined;

    void analyzeNode(ASTNode* node);
    void analyzeVarDecl(ASTNode* node);
    void analyzeFunDecl(ASTNode* node);
    void analyzeCall(ASTNode* node);
    void analyzeId(ASTNode* node);
    void analyzeBinaryOp(ASTNode* node);
    void analyzeUnaryOp(ASTNode* node);
    void analyzeForNode(ASTNode* node);
    void analyzeReturn(ASTNode* node);
    void analyzeCompoundStmt(ASTNode* node);
    void analyzeLBrack(BinaryOpNode* node);
    void analyzeAss(BinaryOpNode* node);

    void calculateLeaveScope(ASTNode* node);
    DataType calcExpType(ExpNode* node);
    bool insertToSymTable(std::string, DeclNode* );
    DeclNode* lookupSymTable(std::string name, unsigned int lineNum, bool use=true, bool warnUninit=true);
    void leaveScope();
};
