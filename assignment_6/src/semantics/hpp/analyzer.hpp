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
    ASTNode* m_ioRoot;
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
    void analyzeBreak(ASTNode* node);
    void analyzeIf(ASTNode* node);
    void analyzeWhile(ASTNode* node);
    void analyzeRange(ASTNode* node);
    void analyzeAss(BinaryOpNode* node);

    void traverseAndSetTypes(ASTNode* node);
    void errorOnWrongParamType(ASTNode* node);
    void checkUsageWarning(bool checkFunc=false);

    void createIOAST();
    void addIOToSymTable();
    void recursiveAddToSym(ASTNode* node);

    void errorOnWrongRangeType(ASTNode* node);
    bool calculateLeaveScope(ASTNode* node, bool isWarn=true);
    bool calculateEnterScope(ASTNode* node);
    DataType calcExpType(ASTNode* node);
    bool insertToSymTable(std::string, DeclNode* );
    DeclNode* lookupSymTable(std::string name, int lineNum, bool use=true, bool warnUninit=true);
    void leaveScope(bool isWarn=true);
};
