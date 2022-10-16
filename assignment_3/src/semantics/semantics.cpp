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
    std::stringstream ss;
    switch (node->getNodeType())
    {
    case NodeType::VarDeclNode:
        analyzeVarDecl(node);
        break;
    case NodeType::FunDeclNode:
        analyzeFunDecl(node);
        break;
    case NodeType::CompoundStmtNode:
        analyzeCompoundStmt(node);
        break;
    case NodeType::IdNode:
        analyzeId(node);
        break;
    case NodeType::CallNode:
        analyzeCall(node);
        break;
    case NodeType::BinaryOpNode:
        analyzeBinaryOp(node);
        break;
    }

    int i=0;
    for (int i=0; i < node->getNumChildren(); i++)
    {
        auto child = node->getChild(i);
        if (child != nullptr)
        {
            analyzeNode(child);
        }
    }

    if (node->getNodeType() == NodeType::CompoundStmtNode)
    {
        leaveScope();
    }

    analyzeNode(node->getSibling(0));
}

void SemanticAnalyzer::analyzeVarDecl(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    auto typedNode = cast<VarDeclNode*>(node);

    bool ok = insertToSymTable(typedNode->getName(), typedNode);

}

void SemanticAnalyzer::analyzeCompoundStmt(ASTNode* node)
{
    auto typedNode = cast<CompoundStmtNode*>(node);
    if (typedNode->getIsFromFunction() == true)
    {
        return;
    }

    std::stringstream ss;
    ss << "Compount Stmt at line: " << node ->getLineNum();
    m_symTable->enter(ss.str());
}

void SemanticAnalyzer::analyzeFunDecl(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    auto funDeclNode = cast<FunDeclNode*>(node);
    std::string funName = funDeclNode->getName();

    insertToSymTable(funName, funDeclNode);

    if (funName == "main" && m_symTable->depth() == 1)
    {
        m_isMainDefined = true;
    }

    std::stringstream ss;
    ss << "Function: " << funName << " at line: " << node->getLineNum();
    m_symTable->enter(ss.str());

    auto params = cast<DeclNode*>(node->getChild(0));
    while (params != nullptr)
    {
        bool ok = insertToSymTable(params->getName(), params);
        params = cast<DeclNode*>(params->getSibling(0));
    }
}

void SemanticAnalyzer::analyzeCall(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    auto callNode = cast<CallNode*>(node);

    std::string funName = callNode->getFunName();
    auto entry = m_symTable->lookup(funName);
    if (entry == nullptr)
    {
        std::stringstream ss;
        ss << "Symbol '" << funName << "' is not declared."; 
        Error::error(node->getLineNum(), ss.str());
        return;
    } else if (entry->getNodeType() != NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << "'" << funName << "' is a simple variable and cannot be called.";
        Error::error(node->getLineNum(), ss.str());
    }

    entry->use();
}

void SemanticAnalyzer::analyzeId(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    auto typedNode = cast<IdNode*>(node);
    std::string idName = typedNode->getIdName();

    auto entry = m_symTable->lookup(idName);
    if (entry == nullptr)
    {
        std::stringstream ss;
        ss << "Symbol '" << idName << "' is not declared.";
        Error::error(node->getLineNum(), ss.str());
        return;
    } else 
    {
        entry->use();
    }

    if (entry->getNodeType() == NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << "Cannot use function '" << idName << "' as a variable.";
        Error::error(node->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeBinaryOp(ASTNode* node)
{
    if (node == nullptr)
    {
        return;
    }
    auto binaryOpNode = cast<BinaryOpNode*>(node);

    switch (binaryOpNode->getOperatorType())
    {
    case BinaryOpType::Index:
        analyzeLBrack(binaryOpNode);
        break;
    case BinaryOpType::Add:
        analyzeAdd(binaryOpNode);
        break;
    case BinaryOpType::Sub:
        analyzeSub(binaryOpNode);
        break;
    case BinaryOpType::Mod:
        analyzeMod(binaryOpNode);
        break;
    case BinaryOpType::Mul:
        analyzeMul(binaryOpNode);
        break;
    case BinaryOpType::Div:
        analyzeDiv(binaryOpNode);
        break;
    }

}

void SemanticAnalyzer::analyzeLBrack(BinaryOpNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    auto left = cast<IdNode*>(node->getChild(0));
    std::string leftName = left->getIdName();
    auto leftDecl = cast<DeclNode*>((ASTNode*)m_symTable->lookup(leftName));
    bool isArr = false;
    if (leftDecl)
    {
        auto leftVarDecl = tryCast<VarDeclNode*>(leftDecl);
        if (leftVarDecl)
        {
            isArr = leftDecl->getDataType().isArray();
        } else
        {
            isArr = false;
        }
    }

    if (!isArr)
    {
        std::stringstream ss;
        ss << "Cannot index nonarray '" << leftName << "'";
        Error::error(node->getLineNum(), ss.str());
    }

    auto right = tryCast<IdNode*>(node->getChild(1));
    if (right)
    {
        if (right->getIdName() == leftName)
        {
            std::stringstream ss;
            ss << "Array index is the unindexed array '" << leftName << "'.";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // convert to expression type.
    //  if expression->getDataType() is not int, then error
}

void SemanticAnalyzer::analyzeAdd(BinaryOpNode* node)
{
    
}

void SemanticAnalyzer::analyzeSub(BinaryOpNode* node)
{
}

void SemanticAnalyzer::analyzeMul(BinaryOpNode* node)
{
}

void SemanticAnalyzer::analyzeDiv(BinaryOpNode* node)
{
}

void SemanticAnalyzer::analyzeMod(BinaryOpNode* node)
{
}

template <typename T> T SemanticAnalyzer::cast(ASTNode* node)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    T typedNode = dynamic_cast<T>(node);
    if (typedNode == nullptr)
    {
        Error::critical(node->getLineNum(), "Could not dynamic_cast<> node");
    }
    return typedNode;
}

template <typename T> T SemanticAnalyzer::tryCast(ASTNode* node)
{
    return dynamic_cast<T>(node);
}

bool SemanticAnalyzer::insertToSymTable(std::string str, DeclNode* node)
{
    bool ok = m_symTable->insert(str, node);
    if (!ok)
    {
        auto originalDecl = (ASTNode*) m_symTable->lookup(str);
        std::stringstream ss;
        ss << "Symbol '" << str << "' is already declared at line "
           << originalDecl->getLineNum();
        Error::error(node->getLineNum(), ss.str());
    }

    return ok;
}

void SemanticAnalyzer::leaveScope()
{
    // check for unused warnings
    auto map = m_symTable->getCurrScopeSymbols();
    for (auto const& [key, val] : map)
    {
        if (val->getUsage() == 0 && val->getNodeType() != NodeType::FunDeclNode)
        {
            std::stringstream ss;
            ss << "The variable '" << key << "' seems not to be used.";
            Error::warning(val->getLineNum(), ss.str());
        }
    }
    m_symTable->leave();
}