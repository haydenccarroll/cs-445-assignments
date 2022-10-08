#include "SemanticsChecker.h"
#include "../Tree/Tree.h"
#include "../SymbolTable/SymbolTable.h"

#include <iostream>

SemanticsChecker::SemanticsChecker() : m_mainIsDefined(false) {}

SemanticsChecker::SemanticsChecker(bool debug)
    : m_mainIsDefined(false), m_debug(debug) {}

const SymbolTable &SemanticsChecker::symbolTable() const {
    return m_symbolTable;
}

int SemanticsChecker::numErrors() const {
    return Message::numErrors() + (!m_mainIsDefined - !m_analyzed);
}

int SemanticsChecker::numWarnings() const { return Message::numWarnings(); }

void SemanticsChecker::print() const {
    if (!m_mainIsDefined) {
        std::cout << "ERROR(LINKER): A function named 'main()' must be defined."
                  << std::endl;
    }

    for (const auto &[lineNumber, bucket] : m_messages) {
        // Iterate backwards through bucket
        for (int i = bucket.size() - 1; i >= 0; i--) {
            auto message = bucket[i];
            std::string tag;

            if (message.type() == Message::MsgType::Error) {
                tag = "ERROR(" + std::to_string(lineNumber) + "): ";
            } else {
                tag = "WARNING(" + std::to_string(lineNumber) + "): ";
            }
            std::cout << tag + message.content() << std::endl;
        }
    }
}

void SemanticsChecker::enterScope() {
    // Use function name as name for the scope
    if (m_scopeName.has_value()) {
        enterScope(m_scopeName.value());
        m_scopeName.reset();
    } else {
        enterScope({});
    }
}

void SemanticsChecker::enterScope(const std::optional<std::string> &name) {
    if (name.has_value()) {
        m_symbolTable.enter(name.value());
    } else {
        m_symbolTable.enter();
    }

    // Add any saved function parameters to the scope
    // Parameters are declared before the scope begins, but exist inside of the
    // scope
    for (auto *parm = m_parms->cast<Tree::Decl::Decl *>(); parm != nullptr;
         parm = parm->sibling()->cast<Tree::Decl::Decl *>()) {

        if (m_symbolTable.containsImmediately(parm->id()) &&
            m_symbolTable[parm->id()].isDeclared()) {
            auto *originalSymbol = m_symbolTable[parm->id()].decl();
            std::string error =
                "Symbol '" + parm->id() + "' is already declared at line " +
                std::to_string(originalSymbol->lineNumber()) + ".";

            m_messages[parm->lineNumber()].push_back(
                {Message::MsgType::Error, error});

        } else {
            m_symbolTable.declare(parm->id(), parm);
        }
    }
    m_parms = nullptr;
}

void SemanticsChecker::leaveScope() {
    auto symbols = m_symbolTable.getImmediateSymbols();

    for (const auto &[id, symbol] : symbols) {

        if (!symbol.isUsed()) {
            std::string warning =
                "The variable '" + id + "' seems not to be used.";

            if (symbol.isDeclared()) {
                m_messages[symbol.decl()->lineNumber()].insert(
                    m_messages[symbol.decl()->lineNumber()].begin(),
                    {Message::MsgType::Warning, warning});
            }
        }

        if (symbol.isDeclared() &&
            symbol.decl()->declType() != Tree::DeclType::Parm &&
            !symbol.decl()->typeInfo().isStatic) {

            if (!symbol.linesUsedBeforeDefined().empty()) {

                auto lineNumber = symbol.linesUsedBeforeDefined().front();
                if (!symbol.isDefined() || lineNumber <= symbol.lineDefined()) {
                    std::string warning =
                        "Variable '" + id +
                        "' may be uninitialized when used here.";

                    m_messages[lineNumber].insert(
                        m_messages[lineNumber].begin(),
                        {Message::MsgType::Warning, warning});
                }
            }
        }
    }

    m_symbolTable.leave();
}

void SemanticsChecker::analyze(Tree::Node *tree) {
    m_analyzed = true;
    m_mainIsDefined = false;
    m_symbolTable = SymbolTable(m_debug);
    m_messages.clear();
    m_numErrors = 0;
    m_numWarnings = 0;
    analyzeTree(tree);
}

void SemanticsChecker::analyzeTree(Tree::Node *tree) {

    // This is where nodes should be analyzed if they are declarations, uses,
    // or definitions. They will be analyzed before their children. Set
    // nodeWasAnalyzed to make sure they do not get analyzed twice.
    bool nodeWasAnalyzed = true;
    if (tree->is(Tree::NodeType::Decl)) {
        analyzeNode(tree->cast<Tree::Decl::Decl *>());
    } else if (tree->is(Tree::ExpType::Id)) {
        analyzeNode(tree->cast<Tree::Exp::Exp *>());
    } else if (tree->is(Tree::ExpType::Call)) {
        analyzeNode(tree->cast<Tree::Exp::Exp *>());
    } else {
        nodeWasAnalyzed = false;
    }

    if (tree->is(Tree::AsgnType::Asgn)) {
        analyzeDefinitions(tree->cast<Tree::Exp::Op::Asgn *>());
    }

    // Entering scopes
    // Compound statements define scopes, but they can share the same scope as
    // a for scope.
    if (tree->is(Tree::StmtType::Compound) &&
        !(tree->parent() != nullptr &&
          tree->parent()->is(Tree::StmtType::For))) {
        if (m_scopeName.has_value()) {
            enterScope(m_scopeName.value());
            m_scopeName.reset();
        } else {
            enterScope("compound");
        }
    } else if (tree->is(Tree::StmtType::For)) {
        enterScope("for");
    }

    // Analyze children of the node
    for (auto &child : tree->children()) {
        if (child != nullptr) {
            analyzeTree(child);
        }
    }

    // If the node wasn't analyzed, then the children were analyzed first
    if (!nodeWasAnalyzed) {
        switch (tree->nodeType()) {
        case Tree::NodeType::Decl: {
            break;
        }
        case Tree::NodeType::Stmt: {
            Tree::Stmt::Stmt *stmt = (Tree::Stmt::Stmt *)tree;
            analyzeNode(stmt);
            break;
        }
        case Tree::NodeType::Exp: {
            Tree::Exp::Exp *exp = (Tree::Exp::Exp *)tree;
            analyzeNode(exp);
            break;
        }
        default:
            break;
        }
    }

    // Handle exiting scopes
    if (tree->is(Tree::StmtType::Compound) &&
        !(tree->parent() != nullptr &&
          tree->parent()->is(Tree::StmtType::For))) {
        leaveScope();
    } else if (tree->is(Tree::StmtType::For)) {
        leaveScope();
    }

    // Analyze siblings
    if (tree->hasSibling()) {
        analyzeTree(tree->sibling());
    }
}

void SemanticsChecker::analyzeDefinitions(Tree::Exp::Op::Asgn *op) {
    if (op->exp1()->is(Tree::ExpType::Id)) {

        bool shouldDefine = true;

        auto *id1 = op->exp1()->cast<Tree::Exp::Id *>();
        if (m_symbolTable[id1->id()].isDeclared() &&
            m_symbolTable[id1->id()].decl()->declType() ==
                Tree::DeclType::Func) {
            shouldDefine = false;
        } else if (op->exp2()->is(Tree::ExpType::Id) &&
                   op->exp2()->cast<Tree::Exp::Id *>()->id() == id1->id()) {
            shouldDefine = false;
        } else if (op->exp2()->cast<Tree::Node *>()->is(
                       Tree::BinaryOpType::Index)) {
            auto *indexOp = op->exp2()->cast<Tree::Exp::Op::Binary *>();
            if (indexOp->exp1()->is(Tree::ExpType::Id) &&
                indexOp->exp1()->cast<Tree::Exp::Id *>()->id() == id1->id()) {
                shouldDefine = false;
            }
        }

        if (shouldDefine) {
            m_symbolTable[id1->id()].define(op->lineNumber());
        }

    } else if (op->exp1()->cast<Tree::Node *>()->is(Tree::BinaryOpType::Index)) {

        auto *indexOp = op->exp1()->cast<Tree::Exp::Op::Binary *>();
        if (indexOp->exp1()->is(Tree::ExpType::Id)) {
            bool shouldDefine = true;

            auto *id1 = indexOp->exp1()->cast<Tree::Exp::Id *>();
            if (m_symbolTable[id1->id()].isDeclared() &&
                m_symbolTable[id1->id()].decl()->declType() ==
                    Tree::DeclType::Func) {
                shouldDefine = false;
            } else if (op->exp2()->is(Tree::ExpType::Id) &&
                       op->exp2()->cast<Tree::Exp::Id *>()->id() == id1->id()) {
                shouldDefine = false;
            } else if (op->exp2()->cast<Tree::Node *>()->is(
                           Tree::BinaryOpType::Index)) {
                auto *indexOp = op->exp2()->cast<Tree::Exp::Op::Binary *>();
                if (indexOp->exp1()->is(Tree::ExpType::Id) &&
                    indexOp->exp1()->cast<Tree::Exp::Id *>()->id() ==
                        id1->id()) {
                    shouldDefine = false;
                }
            }

            if (shouldDefine) {
                m_symbolTable[id1->id()].define(op->lineNumber());
            }
        }
    }
}

void SemanticsChecker::analyzeNode(Tree::Decl::Decl *decl) {
    // Check to see if it's defining main()
    if (decl->is(Tree::DeclType::Func)) {
        m_scopeName = decl->id();
        auto *func = decl->cast<Tree::Decl::Func *>();

        m_parms = func->parms();

        if (func->id() == "main") {
            if (!(func->hasParms() &&
                  func->typeInfo().type.value() == Tree::DataType::Void)) {
                m_mainIsDefined = true;
            } else {
                m_mainIsDefined = false;
            }
        }
    }

    // If it's a parameter declaration, that is handled by enterScope()
    if (!decl->is(Tree::DeclType::Parm)) {

        if (m_symbolTable.containsImmediately(decl->id())) {
            if (m_symbolTable[decl->id()].isDeclared()) {

                auto *originalSymbol = m_symbolTable[decl->id()].decl();
                std::string error =
                    "Symbol '" + decl->id() + "' is already declared at line " +
                    std::to_string(originalSymbol->lineNumber()) + ".";

                m_messages[decl->lineNumber()].push_back(
                    {Message::MsgType::Error, error});
            }
        } else {
            m_symbolTable.declare(decl->id(), decl);
        }
    }

    if (decl->is(Tree::DeclType::Var)) {
        auto *var = decl->cast<Tree::Decl::Var *>();

        if (var->isInitialized()) {

            m_symbolTable[decl->id()].define(var->initValue()->lineNumber());
        } else if (decl->parent() != nullptr &&
                   decl->parent()->is(Tree::StmtType::For)) {

            auto *forParent = var->parent()->cast<Tree::Stmt::For *>();
            m_symbolTable[decl->id()].define(
                forParent->range()->from()->lineNumber());
            m_symbolTable[decl->id()].setIterator(true);
        }
    }
}

void SemanticsChecker::analyzeNode(Tree::Exp::Exp *exp) {

    switch (exp->expType()) {
    case Tree::ExpType::Call: {
        Tree::Exp::Call *call = (Tree::Exp::Call *)exp;

        if (!m_symbolTable.contains(call->id())) {

            std::string error = "Symbol '" + call->id() + "' is not declared.";
            m_messages[call->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        } else if (m_symbolTable[call->id()].isDeclared()) {

            m_symbolTable[call->id()].use(call->lineNumber());

            if (m_symbolTable[call->id()].decl()->declType() !=
                Tree::DeclType::Func) {

                std::string error =
                    "'" + call->id() +
                    "' is a simple variable and cannot be called.";
                m_messages[call->lineNumber()].push_back(
                    {Message::MsgType::Error, error});
            } else {
                call->typeInfo() = m_symbolTable[call->id()].decl()->typeInfo();
            }
        }

        break;
    }
    case Tree::ExpType::Id: {
        auto *id = exp->cast<Tree::Exp::Id *>();

        if (m_symbolTable[id->id()].isDeclared()) {
            id->typeInfo() = m_symbolTable[id->id()].decl()->typeInfo();

            if (m_symbolTable[id->id()].decl()->declType() ==
                Tree::DeclType::Func) {

                std::string error =
                    "Cannot use function '" + id->id() + "' as a variable.";
                m_messages[id->lineNumber()].push_back(
                    {Message::MsgType::Error, error});
            } else {
            }

        } else {
            std::string error = "Symbol '" + id->id() + "' is not declared.";
            m_messages[id->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        bool isUsed = true;
        if (id->hasAncestor<Tree::StmtType>(Tree::StmtType::Range)) {
            auto *range =
                id->getClosestAncestor<Tree::StmtType>(Tree::StmtType::Range)
                    ->cast<Tree::Stmt::Range *>();

            if (range->parent() != nullptr) {
                auto *forstmt = range->parent()->cast<Tree::Stmt::For *>();

                if (forstmt->id()->id() == id->id()) {
                    isUsed = false;
                }
            }
        }

        if (isUsed) {
            m_symbolTable[id->id()].use(id->lineNumber());
        }

        break;
    }
    case Tree::ExpType::Op: {
        auto *op = exp->cast<Tree::Exp::Op::Op *>();
        analyzeNode(op);
        break;
    }
    default: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(Tree::Exp::Op::Op *op) {
    op->deduceType();

    switch (op->opType()) {
    case Tree::OpType::Binary: {
        auto *binary = op->cast<Tree::Exp::Op::Binary *>();

        if (binary->is(Tree::BinaryOpType::Add) ||
            binary->is(Tree::BinaryOpType::Div) ||
            binary->is(Tree::BinaryOpType::Mod) ||
            binary->is(Tree::BinaryOpType::Mul) ||
            binary->is(Tree::BinaryOpType::Subtract)) {

            if (binary->exp1()->typeInfo().isArray ||
                binary->exp2()->typeInfo().isArray &&
                    binary->exp1()->typeInfo().type.has_value() &&
                    binary->exp2()->typeInfo().type.has_value()) {
                std::string error =
                    "The operation '" +
                    Tree::Types::toString(binary->binaryOpType()) +
                    "' does not work with arrays.";

                m_messages[binary->lineNumber()].push_back(
                    {Message::MsgType::Error, error});
            }

            if (binary->exp1()->typeInfo().type != Tree::DataType::Int &&
                binary->exp1()->typeInfo().type.has_value()) {
                std::string error =
                    "'" + Tree::Types::toString(binary->binaryOpType()) +
                    "' requires operands of type int but lhs is of type " +
                    Tree::Types::toString(binary->exp1()->typeInfo().type) + ".";
                m_messages[binary->lineNumber()].push_back(
                    {Message::MsgType::Error, error});
            }

            if (binary->exp2()->typeInfo().type != Tree::DataType::Int &&
                binary->exp2()->typeInfo().type.has_value()) {
                std::string error =
                    "'" + Tree::Types::toString(binary->binaryOpType()) +
                    "' requires operands of type int but rhs is of type " +
                    Tree::Types::toString(binary->exp2()->typeInfo().type) + ".";
                m_messages[binary->lineNumber()].push_back(
                    {Message::MsgType::Error, error});
            }

        }

        else {
            switch (binary->binaryOpType()) {
            case Tree::BinaryOpType::Asgn: {
                analyzeNode((Tree::Exp::Op::Asgn *)binary);
                break;
            }
            case Tree::BinaryOpType::Add: {
                break;
            }
            case Tree::BinaryOpType::Bool: {
                analyzeNode((Tree::Exp::Op::Bool *)binary);
                break;
            }
            case Tree::BinaryOpType::Div: {
                break;
            }
            case Tree::BinaryOpType::Index: {

                Tree::Exp::Id *id = (Tree::Exp::Id *)binary->exp1();
                if (!id->typeInfo().isArray) {
                    std::string error =
                        "Cannot index nonarray '" + id->id() + "'.";
                    m_messages[id->lineNumber()].push_back(
                        {Message::MsgType::Error, error});
                }

                auto *index = binary->exp2();
                if (index->expType() == Tree::ExpType::Id) {
                    auto *indexId = index->cast<Tree::Exp::Id *>();

                    if (m_symbolTable[indexId->id()].isDeclared() &&
                        m_symbolTable[indexId->id()]
                            .decl()
                            ->typeInfo()
                            .isArray) {
                        std::string error =
                            "Array index is the unindexed array '" +
                            indexId->id() + "'.";
                        m_messages[binary->lineNumber()].push_back(
                            {Message::MsgType::Error, error});
                    }
                }

                op->typeInfo() = id->typeInfo();
                op->typeInfo().isArray = false;

                if (binary->exp2()->typeInfo().type != Tree::DataType::Int &&
                    binary->exp2()->typeInfo().type.has_value()) {
                    std::string error =
                        "Array '" + id->id() +
                        "' should be indexed by type int but got type " +
                        Tree::Types::toString(binary->exp2()->typeInfo().type) +
                        ".";
                    m_messages[binary->lineNumber()].push_back(
                        {Message::MsgType::Error, error});
                }

                break;
            }
            case Tree::BinaryOpType::Mod: {
                break;
            }
            case Tree::BinaryOpType::Mul: {
                break;
            }
            case Tree::BinaryOpType::Subtract: {
                break;
            }
            }
        }

        break;
    }
    case Tree::OpType::Unary: {
        auto *unaryop = op->cast<Tree::Exp::Op::Unary *>();
        analyzeNode(unaryop);
        break;
    }
    default: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(Tree::Exp::Op::Unary *op) {
    switch (op->unaryOpType()) {
    case Tree::UnaryOpType::Asgn: {
        auto *unaryasgn = op->cast<Tree::Exp::Op::UnaryAsgn *>();

        if (unaryasgn->operand()->typeInfo().isArray &&
            unaryasgn->operand()->typeInfo().type.has_value()) {
            std::string error =
                "The operation '" +
                Tree::Types::toString(unaryasgn->unaryAsgnType()) +
                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (unaryasgn->operand()->typeInfo().type != Tree::DataType::Int &&
            unaryasgn->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + Tree::Types::toString(unaryasgn->unaryAsgnType()) +
                "' requires an operand of type int but was given type " +
                Tree::Types::toString(unaryasgn->operand()->typeInfo().type) +
                ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        break;
    }
    case Tree::UnaryOpType::Chsign: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                Tree::Types::toString(op->unaryOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->operand()->typeInfo().type != Tree::DataType::Int &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + Tree::Types::toString(op->unaryOpType()) +
                "' requires an operand of type int but was given type " +
                Tree::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
        break;
    }
    case Tree::UnaryOpType::Not: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                Tree::Types::toString(op->unaryOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->operand()->typeInfo().type != Tree::DataType::Bool &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + Tree::Types::toString(op->unaryOpType()) +
                "' requires an operand of type bool but was given type " +
                Tree::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
        break;
    }
    case Tree::UnaryOpType::Random: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '?' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->operand()->typeInfo().type != Tree::DataType::Int &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '?' requires an operand of type int but "
                "was given type " +
                Tree::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
        break;
    }
    case Tree::UnaryOpType::Sizeof: {
        if (!op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "The operation 'sizeof' only works with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(Tree::Exp::Op::Asgn *op) {

    if (!op->is(Tree::AsgnType::Asgn)) {
        if (op->exp1()->typeInfo().type != Tree::DataType::Int &&
            op->exp1()->typeInfo().type.has_value()) {
            std::string error =
                "'" + Tree::Types::toString(op->asgnType()) +
                "' requires operands of type int but lhs is of type " +
                Tree::Types::toString(op->exp1()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->exp2()->typeInfo().type != Tree::DataType::Int &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'" + Tree::Types::toString(op->asgnType()) +
                "' requires operands of type int but rhs is of type " +
                Tree::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
    }

    switch (op->asgnType()) {
    case Tree::AsgnType::Asgn: {

        if (op->exp1()->typeInfo().isArray != op->exp2()->typeInfo().isArray) {
            auto isArrayToString = [](bool b) {
                if (b) {
                    return std::string(" is an array");
                } else {
                    return std::string(" is not an array");
                }
            };

            std::string error =
                "'=' requires both operands be arrays or not but lhs" +
                isArrayToString(op->exp1()->typeInfo().isArray) + " and rhs" +
                isArrayToString(op->exp2()->typeInfo().isArray) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->exp1()->typeInfo().type != op->exp2()->typeInfo().type &&
            op->exp1()->typeInfo().type.has_value() &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'=' requires operands of the same type but lhs is type " +
                Tree::Types::toString(op->exp1()->typeInfo().type) +
                " and rhs is type " +
                Tree::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(Tree::Exp::Op::Bool *op) {
    if (op->boolOpType() == Tree::BoolOpType::And ||
        op->boolOpType() == Tree::BoolOpType::Or) {

        if (op->exp1()->typeInfo().isArray ||
            op->exp2()->typeInfo().isArray &&
                op->exp1()->typeInfo().type.has_value() &&
                op->exp2()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                Tree::Types::toString(op->boolOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->exp1()->typeInfo().type != Tree::DataType::Bool &&
            op->exp1()->typeInfo().type.has_value()) {
            std::string error =
                "'" + Tree::Types::toString(op->boolOpType()) +
                "' requires operands of type bool but lhs is of type " +
                Tree::Types::toString(op->exp1()->typeInfo().type) + ".";

            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->exp2()->typeInfo().type != Tree::DataType::Bool) {
            std::string error =
                "'" + Tree::Types::toString(op->boolOpType()) +
                "' requires operands of type bool but rhs is of type " +
                Tree::Types::toString(op->exp2()->typeInfo().type) + ".";

            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
    } else {
        if (op->exp1()->typeInfo().type != op->exp2()->typeInfo().type &&
            op->exp1()->typeInfo().type.has_value() &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'" + Tree::Types::toString(op->boolOpType()) +
                "' requires operands of the same type but lhs is "
                "type " +
                Tree::Types::toString(op->exp1()->typeInfo().type) +
                " and rhs is type " +
                Tree::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }

        if (op->exp1()->typeInfo().isArray != op->exp2()->typeInfo().isArray) {
            auto isArrayToString = [](bool b) {
                if (b) {
                    return std::string(" is an array");
                } else {
                    return std::string(" is not an array");
                }
            };
            std::string error =
                "'" + Tree::Types::toString(op->boolOpType()) +
                "' requires both operands be arrays or not but lhs" +
                isArrayToString(op->exp1()->typeInfo().isArray) + " and rhs" +
                isArrayToString(op->exp2()->typeInfo().isArray) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
    }
}

void SemanticsChecker::analyzeNode(Tree::Stmt::Stmt *stmt) {
    switch (stmt->stmtType()) {
    case Tree::StmtType::Compound: {
        break;
    }
    case Tree::StmtType::For: {
        break;
    }
    case Tree::StmtType::Return: {
        auto *returnNode = stmt->cast<Tree::Stmt::Return *>();
        if (returnNode->exp() != nullptr &&
            returnNode->exp()->typeInfo().isArray) {
            std::string error = "Cannot return an array.";
            m_messages[returnNode->lineNumber()].push_back(
                {Message::MsgType::Error, error});
        }
        break;
    }
    }
}