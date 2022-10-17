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

DataType SemanticAnalyzer::getExpType(ExpNode* node)
{
    if (node == nullptr) { return DataTypeEnum::None; }

    unsigned int lineNum = node->getLineNum();
    std::string name;

    if (node->getNodeType() == NodeType::IdNode)
    {
        name = cast<IdNode*>(node)->getIdName();
        auto declNode = lookupSymTable(name, lineNum, false);
        if (declNode && declNode->getNodeType() == NodeType::VarDeclNode)
        {
            node->setExpType(declNode->getDataType());
            return declNode->getDataType();
        }
        return DataTypeEnum::None;

    } else if (node->getNodeType() == NodeType::CallNode)
    {
        name = cast<CallNode*>(node)->getFunName();
        auto declNode = lookupSymTable(name, lineNum, false);
        if (declNode && declNode->getNodeType() == NodeType::FunDeclNode)
        {
            node->setExpType(declNode->getDataType());
            return declNode->getDataType();
        }
        return DataTypeEnum::None;

    } else if (node->getNodeType() == NodeType::BinaryOpNode)
    {
        auto binaryOpNode = cast<BinaryOpNode*>(node);
        if (binaryOpNode->getOperatorType() == BinaryOpType::Index)
        {
            auto arr = cast<IdNode*>(binaryOpNode->getChild(0));
            auto declNode = lookupSymTable(arr->getIdName(), lineNum, false);
            if (declNode && declNode->getNodeType() == NodeType::VarDeclNode)
            {
                node->setExpType(DataType(declNode->getDataType().getBasicType()));
                return node->getExpType();
            }
            return DataTypeEnum::None;
        } else if (binaryOpNode->getOperatorType() == BinaryOpType::Ass)
        {
            auto lval = cast<ExpNode*>(binaryOpNode->getChild(0));
            node->setExpType(getExpType(lval));
            return node->getExpType();
        }
    }

    return node->getExpType();
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
    case NodeType::ForNode:
        analyzeForNode(node);
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
    case NodeType::UnaryOpNode:
        analyzeUnaryOp(node);
        break;
    case NodeType::ReturnNode:
        analyzeReturn(node);
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

    calculateLeaveScope(node);

    analyzeNode(node->getSibling(0));
}

void SemanticAnalyzer::calculateLeaveScope(ASTNode* node)
{
    auto parentType = NodeType::CompoundStmtNode;
    if (node->getParent() != nullptr)
    {
        parentType = node->getParent()->getNodeType();
    }

    // if a compound statement that isnt child of a fornode, or if it is a fornode
    if ((node->getNodeType() == NodeType::CompoundStmtNode &&
        parentType != NodeType::ForNode) ||
        node->getNodeType() == NodeType::ForNode)
    {
        leaveScope();
    }
}

void SemanticAnalyzer::analyzeVarDecl(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto typedNode = cast<VarDeclNode*>(node);
    insertToSymTable(typedNode->getName(), typedNode);

}

void SemanticAnalyzer::analyzeCompoundStmt(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto parentType = NodeType::CompoundStmtNode;
    if (node->getParent() != nullptr)
    {
        parentType = node->getParent()->getNodeType();
    }

    // if fun decl or for node is parent, dont do anything, they handle it.
    switch (parentType)
    {
        case NodeType::FunDeclNode:
            return;
        case NodeType::ForNode:
            return;
    }

    std::stringstream ss;
    ss << "Compount Stmt at line: " << node ->getLineNum();
    m_symTable->enter(ss.str());
}

void SemanticAnalyzer::analyzeFunDecl(ASTNode* node)
{
    if (node == nullptr) { return; }

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
}

void SemanticAnalyzer::analyzeForNode(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto funDeclNode = cast<ForNode*>(node);


    std::stringstream ss;
    ss << "For at line: " << node->getLineNum();
    m_symTable->enter(ss.str());
}

void SemanticAnalyzer::analyzeCall(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto callNode = cast<CallNode*>(node);
    std::string funName = callNode->getFunName();
    auto entry = lookupSymTable(funName, callNode->getLineNum());
    if (entry == nullptr)
    {
        return;
    }
    
    if (entry->getNodeType() != NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << "'" << funName << "' is a simple variable and cannot be called.";
        Error::error(node->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeId(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto typedNode = cast<IdNode*>(node);
    std::string idName = typedNode->getIdName();

    auto entry = lookupSymTable(idName, typedNode->getLineNum());
    if (entry == nullptr)
    {
        return;
    }

    if (entry->getNodeType() == NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << "Cannot use function '" << idName << "' as a variable.";
        Error::error(node->getLineNum(), ss.str());
    } else
    {
        auto varDecl = cast<VarDeclNode*>(entry);
    }
}

void SemanticAnalyzer::analyzeReturn(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto returnVal = tryCast<ExpNode*>(node->getChild(0));
    if (returnVal)
    {
        if (getExpType(returnVal).isArray())
        {
            Error::error(node->getLineNum(), "Cannot return an array.");
        }
    }
}

void SemanticAnalyzer::analyzeBinaryOp(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto binaryOpNode = cast<BinaryOpNode*>(node);
    auto lval = cast<ExpNode*>(node->getChild(0));
    auto rval = cast<ExpNode*>(node->getChild(1));

    // ignore everything and just do lbrack analysis
    if (binaryOpNode->getOperatorType() == BinaryOpType::Index)
    {
        analyzeLBrack(binaryOpNode);
        return;
    }

    // requires both operands be arrays.... analysis
    switch (binaryOpNode->getOperatorType())
    {
    case BinaryOpType::EQ:
    case BinaryOpType::NEQ:
    case BinaryOpType::LT:
    case BinaryOpType::LEQ:
    case BinaryOpType::GT:
    case BinaryOpType::GEQ:
    case BinaryOpType::Ass:
        if (getExpType(lval).isArray() && !getExpType(rval).isArray() &&
            getExpType(lval) != DataTypeEnum::None &&
            getExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
               << "' requires both operands be arrays or not but lhs is an array"
               << " and rhs is not an array.";
            Error::error(node->getLineNum(), ss.str());
        } else if (!getExpType(lval).isArray() && getExpType(rval).isArray() &&
                    getExpType(lval) != DataTypeEnum::None &&
                    getExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
               << "' requires both operands be arrays or not but lhs is not an array"
               << " and rhs is an array.";
            Error::error(node->getLineNum(), ss.str());
        }
   
        if (getExpType(lval) != getExpType(rval) &&
            getExpType(lval) != DataTypeEnum::None &&
            getExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of the same type but lhs is "
            << getExpType(lval).toString()
            <<  " and rhs is " << getExpType(rval).toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // requires operands of type bool but lhs/rhs is... 
    switch (binaryOpNode->getOperatorType())
    {
    case BinaryOpType::And:
    case BinaryOpType::Or:
        if (getExpType(lval) != DataTypeEnum::Bool &&
            getExpType(lval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type bool "
            <<  "but lhs is " << getExpType(lval).toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }

        if (getExpType(rval) != DataTypeEnum::Bool &&
            getExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type bool "
            <<  "but rhs is " << getExpType(rval).toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // requires operands of type int but lhs/rhs is...
    switch (binaryOpNode->getOperatorType())
    {
    case BinaryOpType::AddAss:
    case BinaryOpType::SubAss:
    case BinaryOpType::MulAss:
    case BinaryOpType::DivAss:
    case BinaryOpType::Add:
    case BinaryOpType::Sub:
    case BinaryOpType::Mul:
    case BinaryOpType::Div:
    case BinaryOpType::Mod:
        if (getExpType(lval) != DataTypeEnum::Int &&
            getExpType(lval) != DataTypeEnum::None) // if is none, it errored above. dont cascade errors.
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type int "
            <<  "but lhs is " << getExpType(lval).toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }

        if (getExpType(rval) != DataTypeEnum::Int &&
            getExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type int "
            <<  "but rhs is " << getExpType(rval).toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // the operation ... does not work with arrays
    switch (binaryOpNode->getOperatorType())
    {
    case BinaryOpType::And:
    case BinaryOpType::Or:
    case BinaryOpType::AddAss:
    case BinaryOpType::SubAss:
    case BinaryOpType::MulAss:
    case BinaryOpType::DivAss:
    case BinaryOpType::Add:
    case BinaryOpType::Sub:
    case BinaryOpType::Mul:
    case BinaryOpType::Div:
    case BinaryOpType::Mod:
        if (getExpType(lval).isArray() || getExpType(rval).isArray())
        {
            std::stringstream ss;
            ss << "The operation '" 
               << binaryOpTypeToStr(binaryOpNode->getOperatorType()) << "' "
               << "does not work with arrays.";
            Error::error(node->getLineNum(), ss.str());
        }
    }
}

void SemanticAnalyzer::analyzeUnaryOp(ASTNode* node)
{
    if (node == nullptr) { return; }


    auto unaryOpNode = cast<UnaryOpNode*>(node);
    auto rval = cast<ExpNode*>(node->getChild(0));

    // Unary ... requires an operand of int but was given ...
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::Dec:
    case UnaryOpType::Inc:
    case UnaryOpType::Chsign:
    case UnaryOpType::Random:
        if (getExpType(rval) != DataType(DataTypeEnum::Int))
        {
            std::stringstream ss;
            ss << "Unary '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' requires an operand of type int but was given "
               << getExpType(rval).toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // Unary ... requires an operand of bool but was given ...
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::Not:
        if (getExpType(rval) != DataType(DataTypeEnum::Bool))
        {
            std::stringstream ss;
            ss << "Unary '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' requires an operand of type bool but was given "
               << getExpType(rval).toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // The operation sizeof only works with arrays
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::SizeOf:
        if (!getExpType(rval).isArray())
        {
            std::stringstream ss;
            ss << "The operation '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' only works with arrays.";
            Error::error(node->getLineNum(), ss.str());
        }
    }


}

void SemanticAnalyzer::analyzeLBrack(BinaryOpNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    bool isArr = false;
    auto left = cast<IdNode*>(node->getChild(0));
    std::string leftName = left->getIdName();
    auto leftDecl = lookupSymTable(leftName, left->getLineNum(), false);
    if (leftDecl)
    {
        auto leftVarDecl = tryCast<VarDeclNode*>(leftDecl);
        if (leftVarDecl)
        {
            isArr = leftDecl->getDataType().isArray();
        }
    }

    if (!isArr)
    {
        std::stringstream ss;
        ss << "Cannot index nonarray '" << leftName << "'.";
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

    auto rightExp = cast<ExpNode*>(node->getChild(1));
    if (getExpType(rightExp) != DataType(DataTypeEnum::Int))
    {
        std::stringstream ss;
        ss << "Array '" << left->getIdName() << "' should be indexed by type int but got "
           << getExpType(rightExp).toString() << ".";
        Error::error(node->getLineNum(), ss.str());
    }
    // convert to expression type.
    //  if expression->getDataType() is not int, then error
}

void SemanticAnalyzer::analyzeAss(BinaryOpNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    auto lvalId = tryCast<IdNode*>(node->getChild(0));
    if (lvalId)
    {
        auto lvalDecl = lookupSymTable(lvalId->getIdName(), lvalId->getLineNum(), false);
        auto lvalVarDecl = tryCast<VarDeclNode*>(lvalDecl);
        if (lvalVarDecl)
        {
            lvalVarDecl->setInitialized(true);
        }
    } else
    {
        auto lvalLbrack = cast<BinaryOpNode*>(node->getChild(0));
        auto array = cast<IdNode*>(lvalLbrack->getChild(0));
        auto arrayDecl = lookupSymTable(array->getIdName(), array->getLineNum(), false);
        auto arrayVarDecl = tryCast<VarDeclNode*>(arrayDecl);
        if (arrayVarDecl)
        {
            arrayVarDecl->setInitialized(true);
        }
    }

    ASTNode* rval = node->getChild(1);
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
    if (node == nullptr)
    {
        return false;
    }

    bool ok = m_symTable->insert(str, node);
    if (!ok)
    {
        auto originalDecl = m_symTable->lookup(str);
        if (originalDecl == nullptr)
        {
            Error::critical(node->getLineNum(), "could not find node in symbol table.");
        }
        std::stringstream ss;
        ss << "Symbol '" << str << "' is already declared at line "
           << originalDecl->getLineNum() << ".";
        Error::error(node->getLineNum(), ss.str());
    }

    return ok;
}

DeclNode* SemanticAnalyzer::lookupSymTable(std::string name, unsigned int lineNum, bool use)
{
    DeclNode* node = m_symTable->lookup(name);
    if (node == nullptr)
    {
        std::stringstream ss;
        ss << "Symbol '" << name << "' is not declared.";
        Error::error(lineNum, ss.str());
        return nullptr;
    }

    auto varDecl = tryCast<VarDeclNode*>(node);
    if (varDecl && use)
    {
        varDecl->use(lineNum);
    }
    return node;
}

void SemanticAnalyzer::leaveScope()
{
    // check for unused warnings
    auto map = m_symTable->getCurrScopeSymbols();
    for (auto const& [key, val] : map)
    {
        auto varDecl = tryCast<VarDeclNode*>(val);
        if (varDecl == nullptr)
        {
            continue;
        }
        if (varDecl->getUsage() == 0)
        {
            std::stringstream ss;
            ss << "The variable '" << key << "' seems not to be used.";
            Error::warning(varDecl->getLineNum(), ss.str());
        }
    }
    m_symTable->leave();
}
