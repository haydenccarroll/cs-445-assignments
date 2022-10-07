#include "SemanticsChecker.hpp"
#include "../AST/AST.hpp"
#include "../SymbolTable/SymbolTable.hpp"

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
        /// Iterate backwards through bucket
        for (int i = bucket.size() - 1; i >= 0; i--) {
            auto message = bucket[i];
            std::string tag;

            if (message.type() == Message::Type::Error) {
                tag = "ERROR(" + std::to_string(lineNumber) + "): ";
            } else {
                tag = "WARNING(" + std::to_string(lineNumber) + "): ";
            }
            std::cout << tag + message.content() << std::endl;
        }
    }
}

void SemanticsChecker::enterScope() {
    /// Use function name as name for the scope
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

    /// Add any saved function parameters to the scope
    /// Parameters are declared before the scope begins, but exist inside of the
    /// scope
    for (auto *parm = m_parms->cast<AST::Decl::Decl *>(); parm != nullptr;
         parm = parm->sibling()->cast<AST::Decl::Decl *>()) {

        if (m_symbolTable.containsImmediately(parm->id()) &&
            m_symbolTable[parm->id()].isDeclared()) {
            auto *originalSymbol = m_symbolTable[parm->id()].decl();
            std::string error =
                "Symbol '" + parm->id() + "' is already declared at line " +
                std::to_string(originalSymbol->lineNumber()) + ".";

            m_messages[parm->lineNumber()].push_back(
                {Message::Type::Error, error});

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
                    {Message::Type::Warning, warning});
            }
        }

        if (symbol.isDeclared() &&
            symbol.decl()->declType() != AST::DeclType::Parm &&
            !symbol.decl()->typeInfo().isStatic) {

            if (!symbol.linesUsedBeforeDefined().empty()) {

                auto linenumber = symbol.linesUsedBeforeDefined().front();
                if (!symbol.isDefined() || linenumber <= symbol.lineDefined()) {
                    std::string warning =
                        "Variable '" + id +
                        "' may be uninitialized when used here.";

                    m_messages[linenumber].insert(
                        m_messages[linenumber].begin(),
                        {Message::Type::Warning, warning});
                }
            }
        }
    }

    m_symbolTable.leave();
}

void SemanticsChecker::analyze(AST::Node *tree) {
    m_analyzed = true;
    m_mainIsDefined = false;
    m_symbolTable = SymbolTable(m_debug);
    m_messages.clear();
    m_numErrors = 0;
    m_numWarnings = 0;
    analyzeTree(tree);
}

void SemanticsChecker::analyzeTree(AST::Node *tree) {

    /// This is where nodes should be analyzed if they are declarations, uses,
    /// or definitions. They will be analyzed before their children. Set
    /// nodeWasAnalyzed to make sure they do not get analyzed twice.
    bool nodeWasAnalyzed = true;
    if (tree->is(AST::NodeType::Decl)) {
        analyzeNode(tree->cast<AST::Decl::Decl *>());
    } else if (tree->is(AST::ExpType::Id)) {
        analyzeNode(tree->cast<AST::Exp::Exp *>());
    } else if (tree->is(AST::ExpType::Call)) {
        analyzeNode(tree->cast<AST::Exp::Exp *>());
    } else {
        nodeWasAnalyzed = false;
    }

    if (tree->is(AST::AsgnType::Asgn)) {
        analyzeDefinitions(tree->cast<AST::Exp::Op::Asgn *>());
    }

    /// Entering scopes
    /// Compound statements define scopes, but they can share the same scope as
    /// a for scope.
    if (tree->is(AST::StmtType::Compound) &&
        !(tree->parent() != nullptr &&
          tree->parent()->is(AST::StmtType::For))) {
        if (m_scopeName.has_value()) {
            enterScope(m_scopeName.value());
            m_scopeName.reset();
        } else {
            enterScope("compound");
        }
    } else if (tree->is(AST::StmtType::For)) {
        enterScope("for");
    }

    /// Analyze children of the node
    for (auto &child : tree->children()) {
        if (child != nullptr) {
            analyzeTree(child);
        }
    }

    /// If the node wasn't analyzed, then the children were analyzed first
    if (!nodeWasAnalyzed) {
        switch (tree->nodeType()) {
        case AST::NodeType::Decl: {
            break;
        }
        case AST::NodeType::Stmt: {
            AST::Stmt::Stmt *stmt = (AST::Stmt::Stmt *)tree;
            analyzeNode(stmt);
            break;
        }
        case AST::NodeType::Exp: {
            AST::Exp::Exp *exp = (AST::Exp::Exp *)tree;
            analyzeNode(exp);
            break;
        }
        default:
            break;
        }
    }

    /// Handle exiting scopes
    if (tree->is(AST::StmtType::Compound) &&
        !(tree->parent() != nullptr &&
          tree->parent()->is(AST::StmtType::For))) {
        leaveScope();
    } else if (tree->is(AST::StmtType::For)) {
        leaveScope();
    }

    /// Analyze siblings
    if (tree->hasSibling()) {
        analyzeTree(tree->sibling());
    }
}

void SemanticsChecker::analyzeDefinitions(AST::Exp::Op::Asgn *op) {
    if (op->exp1()->is(AST::ExpType::Id)) {

        bool shouldDefine = true;

        auto *id1 = op->exp1()->cast<AST::Exp::Id *>();
        if (m_symbolTable[id1->id()].isDeclared() &&
            m_symbolTable[id1->id()].decl()->declType() ==
                AST::DeclType::Func) {
            shouldDefine = false;
        } else if (op->exp2()->is(AST::ExpType::Id) &&
                   op->exp2()->cast<AST::Exp::Id *>()->id() == id1->id()) {
            shouldDefine = false;
        } else if (op->exp2()->cast<AST::Node *>()->is(
                       AST::BinaryOpType::Index)) {
            auto *indexOp = op->exp2()->cast<AST::Exp::Op::Binary *>();
            if (indexOp->exp1()->is(AST::ExpType::Id) &&
                indexOp->exp1()->cast<AST::Exp::Id *>()->id() == id1->id()) {
                shouldDefine = false;
            }
        }

        if (shouldDefine) {
            m_symbolTable[id1->id()].define(op->lineNumber());
        }

    } else if (op->exp1()->cast<AST::Node *>()->is(AST::BinaryOpType::Index)) {

        auto *indexOp = op->exp1()->cast<AST::Exp::Op::Binary *>();
        if (indexOp->exp1()->is(AST::ExpType::Id)) {
            bool shouldDefine = true;

            auto *id1 = indexOp->exp1()->cast<AST::Exp::Id *>();
            if (m_symbolTable[id1->id()].isDeclared() &&
                m_symbolTable[id1->id()].decl()->declType() ==
                    AST::DeclType::Func) {
                shouldDefine = false;
            } else if (op->exp2()->is(AST::ExpType::Id) &&
                       op->exp2()->cast<AST::Exp::Id *>()->id() == id1->id()) {
                shouldDefine = false;
            } else if (op->exp2()->cast<AST::Node *>()->is(
                           AST::BinaryOpType::Index)) {
                auto *indexOp = op->exp2()->cast<AST::Exp::Op::Binary *>();
                if (indexOp->exp1()->is(AST::ExpType::Id) &&
                    indexOp->exp1()->cast<AST::Exp::Id *>()->id() ==
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

void SemanticsChecker::analyzeNode(AST::Decl::Decl *decl) {
    // Check to see if it's defining main()
    if (decl->is(AST::DeclType::Func)) {
        m_scopeName = decl->id();
        auto *func = decl->cast<AST::Decl::Func *>();

        m_parms = func->parms();

        if (func->id() == "main") {
            if (!(func->hasParms() &&
                  func->typeInfo().type.value() == AST::Type::Void)) {
                m_mainIsDefined = true;
            } else {
                m_mainIsDefined = false;
            }
        }
    }

    // If it's a parameter declaration, that is handled by enterScope()
    if (!decl->is(AST::DeclType::Parm)) {

        if (m_symbolTable.containsImmediately(decl->id())) {
            if (m_symbolTable[decl->id()].isDeclared()) {

                auto *originalSymbol = m_symbolTable[decl->id()].decl();
                std::string error =
                    "Symbol '" + decl->id() + "' is already declared at line " +
                    std::to_string(originalSymbol->lineNumber()) + ".";

                m_messages[decl->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }
        } else {
            m_symbolTable.declare(decl->id(), decl);
        }
    }

    if (decl->is(AST::DeclType::Var)) {
        auto *var = decl->cast<AST::Decl::Var *>();

        if (var->isInitialized()) {

            m_symbolTable[decl->id()].define(var->initValue()->lineNumber());
        } else if (decl->parent() != nullptr &&
                   decl->parent()->is(AST::StmtType::For)) {

            auto *forParent = var->parent()->cast<AST::Stmt::For *>();
            m_symbolTable[decl->id()].define(
                forParent->range()->from()->lineNumber());
            m_symbolTable[decl->id()].setIterator(true);
        }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Exp *exp) {

    switch (exp->expType()) {
    case AST::ExpType::Call: {
        AST::Exp::Call *call = (AST::Exp::Call *)exp;

        if (!m_symbolTable.contains(call->id())) {

            std::string error = "Symbol '" + call->id() + "' is not declared.";
            m_messages[call->lineNumber()].push_back(
                {Message::Type::Error, error});
        } else if (m_symbolTable[call->id()].isDeclared()) {

            m_symbolTable[call->id()].use(call->lineNumber());

            if (m_symbolTable[call->id()].decl()->declType() !=
                AST::DeclType::Func) {

                std::string error =
                    "'" + call->id() +
                    "' is a simple variable and cannot be called.";
                m_messages[call->lineNumber()].push_back(
                    {Message::Type::Error, error});
            } else {
                call->typeInfo() = m_symbolTable[call->id()].decl()->typeInfo();
            }
        }

        break;
    }
    case AST::ExpType::Id: {
        auto *id = exp->cast<AST::Exp::Id *>();

        if (m_symbolTable[id->id()].isDeclared()) {
            id->typeInfo() = m_symbolTable[id->id()].decl()->typeInfo();

            if (m_symbolTable[id->id()].decl()->declType() ==
                AST::DeclType::Func) {

                std::string error =
                    "Cannot use function '" + id->id() + "' as a variable.";
                m_messages[id->lineNumber()].push_back(
                    {Message::Type::Error, error});
            } else {
            }

        } else {
            std::string error = "Symbol '" + id->id() + "' is not declared.";
            m_messages[id->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        bool isUsed = true;
        if (id->hasAncestor<AST::StmtType>(AST::StmtType::Range)) {
            auto *range =
                id->getClosestAncestor<AST::StmtType>(AST::StmtType::Range)
                    ->cast<AST::Stmt::Range *>();

            if (range->parent() != nullptr) {
                auto *forstmt = range->parent()->cast<AST::Stmt::For *>();

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
    case AST::ExpType::Op: {
        auto *op = exp->cast<AST::Exp::Op::Op *>();
        analyzeNode(op);
        break;
    }
    default: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Op *op) {
    op->deduceType();

    switch (op->opType()) {
    case AST::OpType::Binary: {
        auto *binary = op->cast<AST::Exp::Op::Binary *>();

        if (binary->is(AST::BinaryOpType::Add) ||
            binary->is(AST::BinaryOpType::Div) ||
            binary->is(AST::BinaryOpType::Mod) ||
            binary->is(AST::BinaryOpType::Mul) ||
            binary->is(AST::BinaryOpType::Subtract)) {

            if (binary->exp1()->typeInfo().isArray ||
                binary->exp2()->typeInfo().isArray &&
                    binary->exp1()->typeInfo().type.has_value() &&
                    binary->exp2()->typeInfo().type.has_value()) {
                std::string error =
                    "The operation '" +
                    AST::Types::toString(binary->binaryOpType()) +
                    "' does not work with arrays.";

                m_messages[binary->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (binary->exp1()->typeInfo().type != AST::Type::Int &&
                binary->exp1()->typeInfo().type.has_value()) {
                std::string error =
                    "'" + AST::Types::toString(binary->binaryOpType()) +
                    "' requires operands of type int but lhs is of type " +
                    AST::Types::toString(binary->exp1()->typeInfo().type) + ".";
                m_messages[binary->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

            if (binary->exp2()->typeInfo().type != AST::Type::Int &&
                binary->exp2()->typeInfo().type.has_value()) {
                std::string error =
                    "'" + AST::Types::toString(binary->binaryOpType()) +
                    "' requires operands of type int but rhs is of type " +
                    AST::Types::toString(binary->exp2()->typeInfo().type) + ".";
                m_messages[binary->lineNumber()].push_back(
                    {Message::Type::Error, error});
            }

        }

        else {
            switch (binary->binaryOpType()) {
            case AST::BinaryOpType::Asgn: {
                analyzeNode((AST::Exp::Op::Asgn *)binary);
                break;
            }
            case AST::BinaryOpType::Add: {
                break;
            }
            case AST::BinaryOpType::Bool: {
                analyzeNode((AST::Exp::Op::Bool *)binary);
                break;
            }
            case AST::BinaryOpType::Div: {
                break;
            }
            case AST::BinaryOpType::Index: {

                AST::Exp::Id *id = (AST::Exp::Id *)binary->exp1();
                if (!id->typeInfo().isArray) {
                    std::string error =
                        "Cannot index nonarray '" + id->id() + "'.";
                    m_messages[id->lineNumber()].push_back(
                        {Message::Type::Error, error});
                }

                auto *index = binary->exp2();
                if (index->expType() == AST::ExpType::Id) {
                    auto *indexId = index->cast<AST::Exp::Id *>();

                    if (m_symbolTable[indexId->id()].isDeclared() &&
                        m_symbolTable[indexId->id()]
                            .decl()
                            ->typeInfo()
                            .isArray) {
                        std::string error =
                            "Array index is the unindexed array '" +
                            indexId->id() + "'.";
                        m_messages[binary->lineNumber()].push_back(
                            {Message::Type::Error, error});
                    }
                }

                op->typeInfo() = id->typeInfo();
                op->typeInfo().isArray = false;

                if (binary->exp2()->typeInfo().type != AST::Type::Int &&
                    binary->exp2()->typeInfo().type.has_value()) {
                    std::string error =
                        "Array '" + id->id() +
                        "' should be indexed by type int but got type " +
                        AST::Types::toString(binary->exp2()->typeInfo().type) +
                        ".";
                    m_messages[binary->lineNumber()].push_back(
                        {Message::Type::Error, error});
                }

                break;
            }
            case AST::BinaryOpType::Mod: {
                break;
            }
            case AST::BinaryOpType::Mul: {
                break;
            }
            case AST::BinaryOpType::Subtract: {
                break;
            }
            }
        }

        break;
    }
    case AST::OpType::Unary: {
        auto *unaryop = op->cast<AST::Exp::Op::Unary *>();
        analyzeNode(unaryop);
        break;
    }
    default: {
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Unary *op) {
    switch (op->unaryOpType()) {
    case AST::UnaryOpType::Asgn: {
        auto *unaryasgn = op->cast<AST::Exp::Op::UnaryAsgn *>();

        if (unaryasgn->operand()->typeInfo().isArray &&
            unaryasgn->operand()->typeInfo().type.has_value()) {
            std::string error =
                "The operation '" +
                AST::Types::toString(unaryasgn->unaryAsgnType()) +
                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (unaryasgn->operand()->typeInfo().type != AST::Type::Int &&
            unaryasgn->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + AST::Types::toString(unaryasgn->unaryAsgnType()) +
                "' requires an operand of type int but was given type " +
                AST::Types::toString(unaryasgn->operand()->typeInfo().type) +
                ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        break;
    }
    case AST::UnaryOpType::Chsign: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                AST::Types::toString(op->unaryOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->operand()->typeInfo().type != AST::Type::Int &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + AST::Types::toString(op->unaryOpType()) +
                "' requires an operand of type int but was given type " +
                AST::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::UnaryOpType::Not: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                AST::Types::toString(op->unaryOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->operand()->typeInfo().type != AST::Type::Bool &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '" + AST::Types::toString(op->unaryOpType()) +
                "' requires an operand of type bool but was given type " +
                AST::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::UnaryOpType::Random: {
        if (op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error = "The operation '?' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->operand()->typeInfo().type != AST::Type::Int &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "Unary '?' requires an operand of type int but "
                "was given type " +
                AST::Types::toString(op->operand()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    case AST::UnaryOpType::Sizeof: {
        if (!op->operand()->typeInfo().isArray &&
            op->operand()->typeInfo().type.has_value()) {
            std::string error =
                "The operation 'sizeof' only works with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Asgn *op) {

    if (!op->is(AST::AsgnType::Asgn)) {
        if (op->exp1()->typeInfo().type != AST::Type::Int &&
            op->exp1()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->asgnType()) +
                "' requires operands of type int but lhs is of type " +
                AST::Types::toString(op->exp1()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->exp2()->typeInfo().type != AST::Type::Int &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->asgnType()) +
                "' requires operands of type int but rhs is of type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
    }

    switch (op->asgnType()) {
    case AST::AsgnType::Asgn: {

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
                {Message::Type::Error, error});
        }

        if (op->exp1()->typeInfo().type != op->exp2()->typeInfo().type &&
            op->exp1()->typeInfo().type.has_value() &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'=' requires operands of the same type but lhs is type " +
                AST::Types::toString(op->exp1()->typeInfo().type) +
                " and rhs is type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    }
}

void SemanticsChecker::analyzeNode(AST::Exp::Op::Bool *op) {
    if (op->boolOpType() == AST::BoolOpType::And ||
        op->boolOpType() == AST::BoolOpType::Or) {

        if (op->exp1()->typeInfo().isArray ||
            op->exp2()->typeInfo().isArray &&
                op->exp1()->typeInfo().type.has_value() &&
                op->exp2()->typeInfo().type.has_value()) {
            std::string error = "The operation '" +
                                AST::Types::toString(op->boolOpType()) +
                                "' does not work with arrays.";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->exp1()->typeInfo().type != AST::Type::Bool &&
            op->exp1()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires operands of type bool but lhs is of type " +
                AST::Types::toString(op->exp1()->typeInfo().type) + ".";

            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }

        if (op->exp2()->typeInfo().type != AST::Type::Bool) {
            std::string error =
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires operands of type bool but rhs is of type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";

            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
    } else {
        if (op->exp1()->typeInfo().type != op->exp2()->typeInfo().type &&
            op->exp1()->typeInfo().type.has_value() &&
            op->exp2()->typeInfo().type.has_value()) {
            std::string error =
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires operands of the same type but lhs is "
                "type " +
                AST::Types::toString(op->exp1()->typeInfo().type) +
                " and rhs is type " +
                AST::Types::toString(op->exp2()->typeInfo().type) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
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
                "'" + AST::Types::toString(op->boolOpType()) +
                "' requires both operands be arrays or not but lhs" +
                isArrayToString(op->exp1()->typeInfo().isArray) + " and rhs" +
                isArrayToString(op->exp2()->typeInfo().isArray) + ".";
            m_messages[op->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
    }
}

void SemanticsChecker::analyzeNode(AST::Stmt::Stmt *stmt) {
    switch (stmt->stmtType()) {
    case AST::StmtType::Compound: {
        break;
    }
    case AST::StmtType::For: {
        break;
    }
    case AST::StmtType::Return: {
        auto *returnNode = stmt->cast<AST::Stmt::Return *>();
        if (returnNode->exp() != nullptr &&
            returnNode->exp()->typeInfo().isArray) {
            std::string error = "Cannot return an array.";
            m_messages[returnNode->lineNumber()].push_back(
                {Message::Type::Error, error});
        }
        break;
    }
    }
}