#pragma once

#include "../ast/ast.hpp"
#include "../symTable/symTable.hpp"

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

    bool isIdInLval(ASTNode* node);

    bool insertToSymTable(std::string, DeclNode* );
    DeclNode* lookupSymTable(std::string name, unsigned int lineNum, bool use=true, bool warnUninit=true);
    void leaveScope();

    /**
     * @brief casts this object to a child class T
     * 
     * @tparam T child class type
     * @return T child class pointer to node
     */
    template <typename T> T cast(ASTNode* node);

    /**
     * @brief casts this object to a child class T
     * 
     * @tparam T child class type
     * @return T child class pointer to node, nullptr if not able to cast
     */
    template <typename T> T tryCast(ASTNode* node);
};
