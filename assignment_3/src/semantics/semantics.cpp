#include "semantics.hpp"

#include "../symTable/symTable.hpp"
#include "../ast/ast.hpp"
#include "../error/error.hpp"

#include <sstream>

SemanticAnalyzer::SemanticAnalyzer(ASTNode* root, SymbolTable* symTable) :
m_root(root),
m_symTable(symTable),
m_isMainDefined(false)
{
}

void SemanticAnalyzer::analyze()
{
    analyzeNode(m_root);
    if (!m_isMainDefined)
    {
        Error::linker("A function named 'main()' must be defined.");
    }
}

void SemanticAnalyzer::analyzeNode(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    switch (node->getNodeType())
    {
    case NodeType::VarDeclNode:
        analyzeVarDecl(node);
        break;
    case NodeType::FunDeclNode:
        analyzeFunDecl(node);
        break;
    case NodeType::CompoundStmtNode:
        std::stringstream ss;
        ss << "Compount Stmt at line: " << node ->getLineNum();
        m_symTable->enter(ss.str());
    }

    analyzeNode(node->getSibling(0));

    // analyze children in some fashion
    // analyze siblings in some fashion
}

void SemanticAnalyzer::analyzeVarDecl(ASTNode* node)
{
    std::cout << "Analyzing Var Decl Node\n";
    VarDeclNode* typedNode = dynamic_cast<VarDeclNode*>(node);
    if (typedNode == nullptr)
    {
        Error::critical(node->getLineNum(), "Node has m_type VarDeclNode, but couldnt be cast to VarDeclNode type");
    }
    
    bool ok = m_symTable->insert(typedNode->getVarName(), node);
    if (!ok)
    {
        ASTNode* originalDecl = (ASTNode*) m_symTable->lookup(typedNode->getVarName());

        std::stringstream ss;
        ss << "Symbol '" << typedNode->getVarName() << "' is already declared at line "
           << originalDecl->getLineNum() << "\n";

        Error::error(typedNode->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeFunDecl(ASTNode* node)
{
    std::cout << "Analyzing Fun Decl Node\n";
    FunDeclNode* typedNode = dynamic_cast<FunDeclNode*>(node);
    if (typedNode == nullptr)
    {
        Error::critical(node->getLineNum(), "Node has m_type FunDeclNode, but couldnt be cast to FunDeclNode type");
    }

    std::string funName = typedNode->getFunName();

    if (funName == "main" && m_symTable->depth() == 1)
    {
        m_isMainDefined = true;
    }
}

void SemanticAnalyzer::analyzeCall(ASTNode* node)
{
    std::cout << "Analyzing Call Node\n";
    CallNode* typedNode = dynamic_cast<CallNode*>(node);
    if (typedNode == nullptr)
    {
        Error::critical(node->getLineNum(), "Node has m_type CallNode, but couldnt be cast to CallNode type");
    }

    std::string funName = typedNode->getFunName();
    ASTNode* entry = (ASTNode*) m_symTable->lookup(funName);
    if (entry == nullptr)
    {
        std::stringstream ss;
        ss << "Symbol '" << funName << "' is not declared."; 
        Error::error(node->getLineNum(), ss.str());
    } else if (entry->getNodeType() != NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << funName << " is a simple variable and cannot be called.";
        Error::error(node->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeId(ASTNode* node)
{
    std::cout << "Analyzing Id Node\n";
    IdNode* typedNode = dynamic_cast<IdNode*>(node);
    if (typedNode == nullptr)
    {
        Error::critical(node->getLineNum(), "Node has m_type IDNode, but couldnt be cast to IDNode* type");
    }
}