#pragma once

#include "../ast/ast.hpp"
#include "../symTable/symbolTable.hpp"

class SemanticAnalyzer
{
public:
    SemanticAnalyzer(ASTNode* root, SymbolTable* symTable);
    void analyze();
private:
    ASTNode* m_root;
    SymbolTable* m_symTable;
};