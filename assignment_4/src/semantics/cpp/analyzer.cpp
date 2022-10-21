#include "../hpp/analyzer.hpp"

#include "../../symTable/include.hpp"
#include "../../ast/include.hpp"
#include "../../error/include.hpp"

#include <sstream>

SemanticAnalyzer::SemanticAnalyzer(ASTNode* root, SymbolTable* symTable) :
m_root(root),
m_symTable(symTable),
m_isMainDefined(false)
{
}

void SemanticAnalyzer::analyze()
{
    m_symTable->enter("traverse and set types");
    traverseAndSetTypes(m_root);
    m_symTable->leave();

    analyzeNode(m_root);
    checkUsageWarning(true); // does this for global scope.
    if (!m_isMainDefined)
    {
        Error::linker("A function named 'main' with no parameters must be defined.");
    }
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
        analyzeRange(node);
    case NodeType::CompoundStmtNode:
        analyzeCompoundStmt(node);
        break;
    case NodeType::IdNode:
        analyzeId(node);
        break;
    case NodeType::IfNode:
        analyzeIf(node);
        break;
    case NodeType::WhileNode:
        analyzeWhile(node);
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
    case NodeType::BreakNode:
        analyzeBreak(node);
        break;
    }
    calculateEnterScope(node);

    for (int i=0; i < node->getNumChildren(); i++)
    {
        analyzeNode(node->getChild(i));
    }

    calculateLeaveScope(node, true);

    analyzeNode(node->getSibling(0));
}

void SemanticAnalyzer::analyzeVarDecl(ASTNode* node)
{
    auto typedNode = cast<VarDeclNode*>(node);
    if (m_symTable->depth() == 1) // its a global variable, so already initialized.
    {
        typedNode->setInitialized(true);
    }

    auto initExp = cast<ExpNode*>(node->getChild(0));
    if (initExp)
    {
        if (!isConstantExp(initExp))
        {
            std::stringstream ss;
            ss << "Initializer for variable '" << typedNode->getName() << "' "
               << "is not a constant expression.";
            Error::error(initExp->getLineNum(), ss.str());
        }

        if (initExp->getExpType().getBasicType() != typedNode->getDataType().getBasicType() &&
            initExp->getExpType() != DataTypeEnum::None &&
            typedNode->getDataType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Initializer for variable '" << typedNode->getName() << "' "
               << typedNode->getDataType().getBasicType().toString(true) << " is "
               << initExp->getExpType().getBasicType().toString(true);
            Error::error(initExp->getLineNum(), ss.str());
        }

        if (initExp->getExpType().isArray() && !typedNode->getDataType().isArray() &&
            initExp->getExpType() != DataTypeEnum::None &&
            typedNode->getDataType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Initializer for variable '" << typedNode->getName() << "' "
               << "requires both operands be arrays or not but variable is not "
               << "an array and rhs is an array.";
            Error::error(initExp->getLineNum(), ss.str());
        }
        
        if (!initExp->getExpType().isArray() && typedNode->getDataType().isArray() &&
            initExp->getExpType() != DataTypeEnum::None &&
            typedNode->getDataType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Initializer for variable '" << typedNode->getName() << "' "
               << "requires both operands be arrays or not but variable is "
               << "an array and rhs is not an array.";
            Error::error(initExp->getLineNum(), ss.str());
        }
    }
    insertToSymTable(typedNode->getName(), typedNode);

}

void SemanticAnalyzer::analyzeCompoundStmt(ASTNode* node)
{
    // all scope stuff is handled in different function
}

void SemanticAnalyzer::analyzeFunDecl(ASTNode* node)
{
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
}

void SemanticAnalyzer::analyzeForNode(ASTNode* node)
{
}

void SemanticAnalyzer::analyzeCall(ASTNode* node)
{
    auto callNode = cast<CallNode*>(node);
    std::string funName = callNode->getFunName();
    auto entry = lookupSymTable(funName, node->getLineNum(), false);
    if (entry == nullptr)
    {
        std::stringstream ss;
        ss << "Symbol '" << funName << "' is not declared.";
        Error::error(node->getLineNum(), ss.str());
        return;
    }

    entry->use(node->getLineNum());
    
    if (entry->getNodeType() != NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << "'" << funName << "' is a simple variable and cannot be called.";
        Error::error(node->getLineNum(), ss.str());

        auto varDecl = cast<VarDeclNode*>(entry);
        varDecl->use(node->getLineNum());
        return;
    }

    errorOnWrongParamType(node);
}




void SemanticAnalyzer::analyzeId(ASTNode* node)
{
    bool warnUninit = !isIdInLval(node);

    auto typedNode = cast<IdNode*>(node);
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

void SemanticAnalyzer::analyzeReturn(ASTNode* node)
{
    auto returnVal = tryCast<ExpNode*>(node->getChild(0));
    auto funcDecl = cast<FunDeclNode*>(node->getAncestor(NodeType::FunDeclNode));
    if (returnVal)
    {
        if (returnVal->getExpType().isArray())
        {
            Error::error(node->getLineNum(), "Cannot return an array.");
        }

        if (funcDecl->getDataType() == DataTypeEnum::Void)
        {

            std::stringstream ss;
            ss << "Function '" << funcDecl->getName() << "' at line " 
               << funcDecl->getLineNum() << " is expecting no return value, but "
               << "return has a value.";
            Error::error(node->getLineNum(), ss.str());
        } else if (funcDecl->getDataType().getBasicType() 
                   != returnVal->getExpType().getBasicType() &&
                   funcDecl->getDataType() != DataTypeEnum::None &&
                   returnVal->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Function '" << funcDecl->getName() << "' at line " 
               << funcDecl->getLineNum() << " is expecting to return "
               << funcDecl->getDataType().getBasicType().toString(false)
               << " but returns " << returnVal->getExpType().getBasicType().toString(false)
               << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    } else
    {
        if (funcDecl->getDataType() != DataTypeEnum::Void)
        {
            std::stringstream ss;
            ss << "Function '" << funcDecl->getName() << "' at line " 
               << funcDecl->getLineNum() << " is expecting to return "
               << funcDecl->getDataType().getBasicType().toString(false)
               << " but return has no value.";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    funcDecl->incrementNumReturn();
}

void SemanticAnalyzer::analyzeBinaryOp(ASTNode* node)
{
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
        if (lval->getExpType().isArray() && !rval->getExpType().isArray() &&
            lval->getExpType() != DataTypeEnum::None &&
            rval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
               << "' requires both operands be arrays or not but lhs is an array"
               << " and rhs is not an array.";
            Error::error(node->getLineNum(), ss.str());
        } else if (!lval->getExpType().isArray() && rval->getExpType().isArray() &&
                    lval->getExpType() != DataTypeEnum::None &&
                    rval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
               << "' requires both operands be arrays or not but lhs is not an array"
               << " and rhs is an array.";
            Error::error(node->getLineNum(), ss.str());
        }
   
        if (lval->getExpType().getBasicType() != rval->getExpType().getBasicType() &&
            lval->getExpType() != DataTypeEnum::None &&
            rval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of the same type but lhs is "
            << lval->getExpType().getBasicType().toString(false)
            <<  " and rhs is " << rval->getExpType().getBasicType().toString(false) << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // requires operands of type bool but lhs/rhs is... 
    switch (binaryOpNode->getOperatorType())
    {
    case BinaryOpType::And:
    case BinaryOpType::Or:
        if (lval->getExpType().getBasicType() != DataTypeEnum::Bool &&
            lval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type bool "
            <<  "but lhs is " << lval->getExpType().getBasicType().toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }

        if (rval->getExpType().getBasicType() != DataTypeEnum::Bool &&
            rval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type bool "
            <<  "but rhs is " << rval->getExpType().getBasicType().toString() << ".";
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
        if (lval->getExpType().getBasicType() != DataTypeEnum::Int &&
            lval->getExpType() != DataTypeEnum::None) // if is none, it errored above. dont cascade errors.
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type int "
            <<  "but lhs is " << lval->getExpType().getBasicType().toString() << ".";
            Error::error(node->getLineNum(), ss.str());
        }

        if (rval->getExpType().getBasicType() != DataTypeEnum::Int &&
            rval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "'" << binaryOpTypeToStr(binaryOpNode->getOperatorType())
            << "' requires operands of type int "
            <<  "but rhs is " << rval->getExpType().getBasicType().toString() << ".";
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
        if (lval->getExpType().isArray() || rval->getExpType().isArray())
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
        if (rval->getExpType().isArray())
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
        if (rval->getExpType().getBasicType() != DataType(DataTypeEnum::Int) && 
            rval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Unary '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' requires an operand of type int but was given "
               << rval->getExpType().getBasicType().toString(false) << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // Unary ... requires an operand of bool but was given ...
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::Not:
        if (rval->getExpType().getBasicType() != DataTypeEnum::Bool && 
            rval->getExpType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Unary '" << unaryOpTypeToStr(unaryOpNode->getOperatorType())
               << "' requires an operand of type bool but was given "
               << rval->getExpType().getBasicType().toString(false) << ".";
            Error::error(node->getLineNum(), ss.str());
        }
    }

    // The operation sizeof only works with arrays
    switch (unaryOpNode->getOperatorType())
    {
    case UnaryOpType::SizeOf:
        if (!rval->getExpType().isArray() && 
            rval->getExpType() != DataTypeEnum::None)
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
    if (rightExp->getExpType().getBasicType() != DataType(DataTypeEnum::Int) && 
        rightExp->getExpType() != DataTypeEnum::None)
    {
        std::stringstream ss;
        ss << "Array '" << left->getIdName() << "' should be indexed by type int but got "
           << rightExp->getExpType().getBasicType().toString(false) << ".";
        Error::error(node->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeAss(BinaryOpNode* node)
{
    // analyze right side first
    analyzeNode(node->getChild(1));

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

void SemanticAnalyzer::analyzeBreak(ASTNode* node)
{
    auto parent = node;
    while (parent != nullptr)
    {
        parent = parent->getParent();
    }
    if (!node->hasAncestor(NodeType::WhileNode) &&
        !node->hasAncestor(NodeType::ForNode))
    {
        Error::error(node->getLineNum(), 
                     "Cannot have a break statement outside of loop.");
    }
}

void SemanticAnalyzer::analyzeIf(ASTNode* node)
{
    auto condition = cast<ExpNode*>(node->getChild(0));
    if (isArray(condition))
    {
        Error::error(condition->getLineNum(), 
                     "Cannot use array as test condition in if statement.");
    }


    if (condition->getExpType().getBasicType() != DataTypeEnum::Bool &&
        condition->getExpType() != DataTypeEnum::None)
    {
        std::stringstream ss;
        ss << "Expecting Boolean test condition in if statement but got "
           << condition->getExpType().getBasicType().toString(false) << ".";
        Error::error(condition->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeWhile(ASTNode* node)
{
    auto condition = cast<ExpNode*>(node->getChild(0));
    if (isArray(condition))
    {
        Error::error(condition->getLineNum(), 
                     "Cannot use array as test condition in while statement.");
    }

    if (condition->getExpType().getBasicType() != DataTypeEnum::Bool &&
        condition->getExpType() != DataTypeEnum::None)
    {
        std::stringstream ss;
        ss << "Expecting Boolean test condition in while statement but got "
           << condition->getExpType().getBasicType().toString(false) << ".";
        Error::error(condition->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::analyzeRange(ASTNode* node)
{
    for (int i=0; i < node->getNumChildren(); i++)
    {
        ASTNode* child = node->getChild(i);
        if (child == nullptr)
        {
            continue;
        }

        if (isArray(child))
        {
            std::stringstream ss;
            ss << "Cannot use array in position " << i+1
               << " in range of for statement.";
            Error::error(child->getLineNum(), ss.str());
        }
    }

    errorOnWrongRangeType(node);
}

void SemanticAnalyzer::errorOnWrongParamType(ASTNode* node)
{
    if (node == nullptr || node->getNodeType() != NodeType::CallNode)
    {
        return;
    }
    auto call = cast<CallNode*>(node);

    auto funDecl = tryCast<FunDeclNode*>(lookupSymTable(call->getFunName(), call->getLineNum(), false, false));
    if (funDecl == nullptr)
    {
        return;
    }

    auto currArg = cast<ExpNode*>(call->getChild(0));
    auto currParam = cast<VarDeclNode*>(funDecl->getChild(0));
    unsigned int i = 1;
    while (currArg != nullptr && currParam != nullptr)
    {
        DataType argType = currArg->getExpType();
        DataType paramType = currParam->getDataType();
        if (argType.getBasicType() != paramType.getBasicType() &&
            argType != DataTypeEnum::None &&
            paramType != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Expecting " << paramType.getBasicType().toString(false) 
               << " in parameter " << i << " of call to '" << call->getFunName()
               << "' declared on line " << funDecl->getLineNum() << " but got "
               << argType.getBasicType().toString(false) << ".";
            Error::error(currArg->getLineNum(), ss.str());
        }

        if (!argType.isArray() && paramType.isArray() &&
            argType != DataTypeEnum::None &&
            paramType != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Expecting array in parameter "
               << i << " of call to '" << call->getFunName()
               << "' declared on line " << funDecl->getLineNum() << ".";
            Error::error(currArg->getLineNum(), ss.str());
        }

        if (argType.isArray() && !paramType.isArray() &&
            argType != DataTypeEnum::None &&
            paramType != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Not expecting array in parameter "
               << i << " of call to '" << call->getFunName()
               << "' declared on line " << funDecl->getLineNum() << ".";
            Error::error(currArg->getLineNum(), ss.str());
        }
        currArg = cast<ExpNode*>(currArg->getSibling(0));
        currParam = cast<VarDeclNode*>(currParam->getSibling(0));
        i++;
    }

    unsigned int numArgs = i;
    unsigned int numParams = i;
    while (currArg != nullptr)
    {
        currArg = cast<ExpNode*>(currArg->getSibling(0));
        numArgs++;
    }

    while (currParam != nullptr)
    {
        currParam = cast<VarDeclNode*>(currParam->getSibling(0));
        numParams++;
    }

    if (numArgs < numParams)
    {
        std::stringstream ss;
        ss << "Too few parameters passed for function '" << funDecl->getName()
           << "' declared on line " << funDecl->getLineNum() << ".";
        Error::error(node->getLineNum(), ss.str());
    } else if (numArgs > numParams)
    {
        std::stringstream ss;
        ss << "Too many parameters passed for function '" << funDecl->getName()
           << "' declared on line " << funDecl->getLineNum() << ".";
        Error::error(node->getLineNum(), ss.str());
    }
}

void SemanticAnalyzer::errorOnWrongRangeType(ASTNode* node)
{
    if (node == nullptr || node->getNodeType() != NodeType::RangeNode)
    {
        return;
    }
    
    for (int i=0; i < node->getNumChildren(); i++)
    {
        ASTNode* child = node->getChild(i);
        if (child == nullptr)
        {
            continue;
        }
        auto childExp = cast<ExpNode*>(child);
        if (childExp->getExpType().getBasicType() != DataTypeEnum::Int &&
            childExp->getExpType().getBasicType() != DataTypeEnum::None)
        {
            std::stringstream ss;
            ss << "Expecting type int in position "
               << i+1 << " in range of for statement but got "
               << childExp->getExpType().getBasicType().toString(false) << ".";
            Error::error(childExp->getLineNum(), ss.str());
        }
    }

}

void SemanticAnalyzer::traverseAndSetTypes(ASTNode* node)
{
    if (node == nullptr) { return; }

    if (node->getNodeType() == NodeType::VarDeclNode)
    {
        auto varDecl = cast<VarDeclNode*>(node);
        m_symTable->insert(varDecl->getName(), varDecl);
    } else if (node->getNodeType() == NodeType::FunDeclNode)
    {
        auto funDecl = cast<FunDeclNode*>(node);
        m_symTable->insert(funDecl->getName(), funDecl);
    }

    calcExpType(node);
    calculateEnterScope(node);

    for (int i=0; i < node->getNumChildren(); i++)
    {
        traverseAndSetTypes(node->getChild(i));
    }

    calculateLeaveScope(node, false);

    traverseAndSetTypes(node->getSibling(0));
}

DataType SemanticAnalyzer::calcExpType(ASTNode* node)
{
    if (node == nullptr || tryCast<ExpNode*>(node) == nullptr) 
    {
        return DataTypeEnum::None;
    }

    auto expNode = cast<ExpNode*>(node);

    unsigned int lineNum = expNode->getLineNum();
    std::string name;

    if (expNode->getNodeType() == NodeType::IdNode)
    {
        name = cast<IdNode*>(expNode)->getIdName();
        auto declNode = m_symTable->lookup(name);
        if (declNode && declNode->getNodeType() == NodeType::VarDeclNode)
        {
            expNode->setExpType(declNode->getDataType());
        }
    } else if (expNode->getNodeType() == NodeType::CallNode)
    {
        name = cast<CallNode*>(expNode)->getFunName();
        auto declNode = m_symTable->lookup(name);
        if (declNode && declNode->getNodeType() == NodeType::FunDeclNode)
        {
            expNode->setExpType(declNode->getDataType());
        }
    
    } else if (expNode->getNodeType() == NodeType::BinaryOpNode)
    {
        auto binaryOpNode = cast<BinaryOpNode*>(expNode);
        auto lval = cast<ExpNode*>(expNode->getChild(0));
        auto rval = cast<ExpNode*>(expNode->getChild(1));

        if (binaryOpNode->getOperatorType() == BinaryOpType::Index ||
            binaryOpNode->getOperatorType() == BinaryOpType::Ass)
        {
            expNode->setExpType(calcExpType(lval).getBasicType());
        } else if (calcExpType(lval) == DataTypeEnum::None || 
                   calcExpType(rval) == DataTypeEnum::None)
        {
            expNode->setExpType(DataTypeEnum::None);
        }
    } else if (expNode->getNodeType() == NodeType::UnaryOpNode)
    {
        auto rval = cast<ExpNode*>(expNode->getChild(0));
        if (calcExpType(rval) == DataTypeEnum::None)
        {
            expNode->setExpType(DataTypeEnum::None);
        }
    }

    return expNode->getExpType();
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

    if (use)
    {
        node->use(lineNum, warnUninit);
    }
    return node;
}

void SemanticAnalyzer::calculateLeaveScope(ASTNode* node, bool isWarn)
{
    auto parentType = NodeType::CompoundStmtNode;
    if (node->getParent() != nullptr)
    {
        parentType = node->getParent()->getNodeType();
    }

    // if a compound statement that isnt child of a fornode, or if it is a fornode
    if (node->getNodeType() == NodeType::ForNode ||
        node->getNodeType() == NodeType::FunDeclNode ||
        (node->getNodeType() == NodeType::CompoundStmtNode &&
        (parentType != NodeType::ForNode && parentType != NodeType::FunDeclNode))
        
        )
    {
        auto funDecl = tryCast<FunDeclNode*>(node);
        if (funDecl != nullptr)
        {
            if (funDecl->getNumReturn() == 0 && isWarn &&
                (funDecl->getDataType() != DataTypeEnum::Void &&
                 funDecl->getDataType() != DataTypeEnum::None))
            {
                std::stringstream ss;
                ss << "Expecting to return " 
                << funDecl->getDataType().getBasicType().toString(false)
                << " but function '" << funDecl->getName() << "' has no return statement.";
                Error::warning(funDecl->getLineNum(), ss.str());
            }
        }
        leaveScope(isWarn);
    }
}

void SemanticAnalyzer::calculateEnterScope(ASTNode* node)
{
    if (node->getNodeType() == NodeType::CompoundStmtNode)
    {
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
        return;
    }

    else if (node->getNodeType() == NodeType::ForNode)
    {
        std::stringstream ss;
        ss << "For loop at line: " << node->getLineNum();
        m_symTable->enter(ss.str());
    }

    else if (node->getNodeType() == NodeType::FunDeclNode)
    {
        std::stringstream ss;
        ss << "Func decl at line: " << node->getLineNum();
        m_symTable->enter(ss.str());
    }
}

void SemanticAnalyzer::leaveScope(bool isWarn)
{

    // check for unused warnings
    if (isWarn)
    {
        checkUsageWarning(false);
    }
    m_symTable->leave();
}

void SemanticAnalyzer::checkUsageWarning(bool checkFunc)
{
    // check for unused warnings
    auto map = m_symTable->getCurrScopeSymbols();
    for (auto const& [key, val] : map)
    {
        auto varDecl = tryCast<VarDeclNode*>(val);
        auto funDecl = tryCast<FunDeclNode*>(val);
        if (varDecl != nullptr)
        {
            if (varDecl->getUsage() == 0)
            {
                std::stringstream ss;
                if (varDecl->isParam())
                {
                    ss << "The parameter '";
                } else
                {
                    ss << "The variable '";
                }
                ss << key << "' seems not to be used.";
                Error::warning(varDecl->getLineNum(), ss.str());
            }
        }
        else if (funDecl != nullptr)
        {
            if (funDecl->getUsage() == 0 && funDecl->getName() != "main")
            {
                std::stringstream ss;
                ss << "The function '" << key << "' seems not to be used.";
                Error::warning(funDecl->getLineNum(), ss.str());
            }
        }
    }
}