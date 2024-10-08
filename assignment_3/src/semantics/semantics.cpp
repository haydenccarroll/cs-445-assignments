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

DataType SemanticAnalyzer::calcExpType(ExpNode* node)
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
        }
    } else if (node->getNodeType() == NodeType::CallNode)
    {
        name = cast<CallNode*>(node)->getFunName();
        auto declNode = lookupSymTable(name, lineNum, false);
        if (declNode && declNode->getNodeType() == NodeType::FunDeclNode)
        {
            node->setExpType(declNode->getDataType());
        }
    
    } else if (node->getNodeType() == NodeType::BinaryOpNode)
    {
        auto binaryOpNode = cast<BinaryOpNode*>(node);
        auto lval = cast<ExpNode*>(node->getChild(0));
        auto rval = cast<ExpNode*>(node->getChild(1));

        if (binaryOpNode->getOperatorType() == BinaryOpType::Index ||
            binaryOpNode->getOperatorType() == BinaryOpType::Ass)
        {
            node->setExpType(calcExpType(lval).getBasicType());
        } else if (calcExpType(lval) == DataTypeEnum::None || 
                   calcExpType(rval) == DataTypeEnum::None)
        {
            node->setExpType(DataTypeEnum::None);
        }
    } else if (node->getNodeType() == NodeType::UnaryOpNode)
    {
        auto rval = cast<ExpNode*>(node->getChild(0));
        if (calcExpType(rval) == DataTypeEnum::None)
        {
            node->setExpType(DataTypeEnum::None);
        }


    }

    return node->getExpType();
}

void SemanticAnalyzer::analyzeNode(ASTNode* node)
{
    if (node == nullptr || node->getHasBeenAnalyzed()) { return; }
    node->setHasBeenAnalyzed(true);

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
    case NodeType::RangeNode: // for whatever reason, we dont analyze anything in range node.
        return;
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

    for (int i=0; i < node->getNumChildren(); i++)
    {
        analyzeNode(node->getChild(i));
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
    if (m_symTable->depth() == 1) // its a global variable, so already initialized.
    {
        typedNode->setInitialized(true);
    }
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

    // a function named main exists, with no parameters, and has at least one thing
    // inside its compound statement
    if (funName == "main" && m_symTable->depth() == 1 &&
        funDeclNode->getChild(0) == nullptr)
    {
        auto compoundStmt = cast<CompoundStmtNode*>(funDeclNode->getChild(1));
        if (compoundStmt->getChild(0) != nullptr || compoundStmt->getChild(1) != nullptr)
        {
            m_isMainDefined = true;
        }
    }

    // a function named main exists, with no parameters, and has no return type.
    if (funName == "main" && m_symTable->depth() == 1 &&
        funDeclNode->getChild(0) == nullptr &&
        funDeclNode->getDataType() == DataTypeEnum::Void)
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
    calcExpType(callNode);
    std::string funName = callNode->getFunName();
    auto entry = lookupSymTable(funName, node->getLineNum(), false);
    if (entry == nullptr)
    {
        std::stringstream ss;
        ss << "Symbol '" << funName << "' is not declared.";
        Error::error(node->getLineNum(), ss.str());
        return;
    }
    
    if (entry->getNodeType() != NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << "'" << funName << "' is a simple variable and cannot be called.";
        Error::error(node->getLineNum(), ss.str());

        auto varDecl = cast<VarDeclNode*>(entry);
        varDecl->use(node->getLineNum());
    }
}

void SemanticAnalyzer::analyzeId(ASTNode* node)
{
    if (node == nullptr) { return; }
    bool warnUninit = !isIdInLval(node);

    auto typedNode = cast<IdNode*>(node);
    calcExpType(typedNode);
    std::string idName = typedNode->getIdName();

    auto entry = lookupSymTable(idName, node->getLineNum(), true, warnUninit);
    if (entry == nullptr)
    {
        std::stringstream ss;
        ss << "Symbol '" << idName << "' is not declared.";
        Error::error(node->getLineNum(), ss.str());
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

bool SemanticAnalyzer::isIdInLval(ASTNode* node)
{
    if (node == nullptr) { return false; }

    auto ancestor = cast<BinaryOpNode*>(node->getAncestor(NodeType::BinaryOpNode));
    while (ancestor != nullptr)
    {
        switch (ancestor->getOperatorType())
        {
        case BinaryOpType::Ass:
        case BinaryOpType::AddAss:
        case BinaryOpType::MulAss:
        case BinaryOpType::DivAss:
            if (node->isAncestor(ancestor->getChild(0)))
            {
                return true;
            }
        }
        ancestor = cast<BinaryOpNode*>(ancestor->getAncestor(NodeType::BinaryOpNode));
    }

    return false;
}

void SemanticAnalyzer::analyzeReturn(ASTNode* node)
{
    if (node == nullptr) { return; }

    auto returnVal = tryCast<ExpNode*>(node->getChild(0));
    if (returnVal)
    {
        if (calcExpType(returnVal).isArray())
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

    switch(binaryOpNode->getOperatorType())
    {
    case BinaryOpType::AddAss:
    case BinaryOpType::SubAss:
    case BinaryOpType::MulAss:
    case BinaryOpType::DivAss:
    case BinaryOpType::Ass:
        analyzeAss(binaryOpNode);
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
        if (calcExpType(lval).isArray() && !calcExpType(rval).isArray() &&
            calcExpType(lval) != DataTypeEnum::None &&
            calcExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
               << "' requires both operands be arrays or not but lhs is an array"
               << " and rhs is not an array.";
            Error::error(node->getLineNum(), ss.str());
        } else if (!calcExpType(lval).isArray() && calcExpType(rval).isArray() &&
                    calcExpType(lval) != DataTypeEnum::None &&
                    calcExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
               << "' requires both operands be arrays or not but lhs is not an array"
               << " and rhs is an array.";
            Error::error(node->getLineNum(), ss.str());
        }
   
        if (calcExpType(lval).getBasicType() != calcExpType(rval).getBasicType() &&
            calcExpType(lval) != DataTypeEnum::None &&
            calcExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of the same type but lhs is "
            << calcExpType(lval).getBasicType().toString(false)
            <<  " and rhs is " << calcExpType(rval).getBasicType().toString(false) << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // requires operands of type bool but lhs/rhs is... 
    switch (binaryOpNode->getOperatorType())
    {
    case BinaryOpType::And:
    case BinaryOpType::Or:
        if (calcExpType(lval).getBasicType() != DataTypeEnum::Bool &&
            calcExpType(lval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type bool "
            <<  "but lhs is " << calcExpType(lval).getBasicType().toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }

        if (calcExpType(rval).getBasicType() != DataTypeEnum::Bool &&
            calcExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type bool "
            <<  "but rhs is " << calcExpType(rval).getBasicType().toString() << ".";
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
        if (calcExpType(lval).getBasicType() != DataTypeEnum::Int &&
            calcExpType(lval) != DataTypeEnum::None) // if is none, it errored above. dont cascade errors.
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type int "
            <<  "but lhs is " << calcExpType(lval).getBasicType().toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }

        if (calcExpType(rval).getBasicType() != DataTypeEnum::Int &&
            calcExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type int "
            <<  "but rhs is " << calcExpType(rval).getBasicType().toString() << ".";
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
        if (calcExpType(lval).isArray() || calcExpType(rval).isArray())
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

    // The operation ... does not work with arrays.
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::Dec:
    case UnaryOpType::Inc:
    case UnaryOpType::Chsign:
    case UnaryOpType::Random:
    case UnaryOpType::Not:
        if (calcExpType(rval).isArray())
        {
            std::stringstream ss;
            ss << "The operation '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' does not work with arrays.";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // Unary ... requires an operand of int but was given ...
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::Dec:
    case UnaryOpType::Inc:
    case UnaryOpType::Chsign:
    case UnaryOpType::Random:
        if (calcExpType(rval).getBasicType() != DataType(DataTypeEnum::Int) && 
            calcExpType(rval) != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Unary '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' requires an operand of type int but was given "
               << calcExpType(rval).getBasicType().toString(false) << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // Unary ... requires an operand of bool but was given ...
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::Not:
        if (calcExpType(rval).getBasicType() != DataType(DataTypeEnum::Bool) && 
            calcExpType(rval) != DataTypeEnum::Void)
        {
            std::stringstream ss;
            ss << "Unary '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' requires an operand of type bool but was given "
               << calcExpType(rval).getBasicType().toString(false) << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // The operation sizeof only works with arrays
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::SizeOf:
        if (!calcExpType(rval).isArray() && 
            calcExpType(rval) != DataTypeEnum::None)
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

    calcExpType(node);

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
        if (leftName.compare(right->getIdName()) == 0 && isArr)
        {
            std::stringstream ss;
            ss << "Array index is the unindexed array '" << leftName << "'.";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    auto rightExp = cast<ExpNode*>(node->getChild(1));
    if (calcExpType(rightExp).getBasicType() != DataType(DataTypeEnum::Int) && 
        calcExpType(rightExp) != DataTypeEnum::None)
    {
        std::stringstream ss;
        ss << "Array '" << left->getIdName() << "' should be indexed by type int but got "
           << calcExpType(rightExp).getBasicType().toString(false) << ".";
        Error::error(node->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeAss(BinaryOpNode* node)
{
    if (node == nullptr)
    {
        return;
    }

    // analyze right side first
    analyzeNode(node->getChild(1));
    calcExpType(node);

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

DeclNode* SemanticAnalyzer::lookupSymTable(std::string name, unsigned int lineNum, bool use, bool warnUninit)
{
    DeclNode* node = m_symTable->lookup(name);
    if (node == nullptr)
    {
        return nullptr;
    }

    auto varDecl = tryCast<VarDeclNode*>(node);
    if (varDecl && use == true)
    {
        varDecl->use(lineNum, warnUninit);
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
