#pragma once

#include "../ast/ast.hpp"
#include "../symTable/symTable.hpp"

class SemanticAnalyzer
{
public:
    SemanticAnalyzer(ASTNode* root, SymbolTable* symTable);
    void analyze();
    void analyzeNode(ASTNode* node);
    void analyzeVarDecl(ASTNode* node);
    void analyzeFunDecl(ASTNode* node);
    void analyzeCall(ASTNode* node);
    void analyzeId(ASTNode* node);
private:
    ASTNode* m_root;
    SymbolTable* m_symTable;
    bool m_isMainDefined;
};