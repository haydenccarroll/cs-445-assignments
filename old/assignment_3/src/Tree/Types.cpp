#include "Types.h"

namespace Tree::Types {
std::string toString(DataType t) {
    switch (t) {
    case DataType::Bool:
        return "bool";
    case DataType::Char:
        return "char";
    case DataType::Int:
        return "int";
    case DataType::Void:
        return "void";
    default:
        return "type";
    }
}

std::string toString(std::optional<DataType> type) {
    if (type.has_value()) {
        return toString(type.value());
    } else {
        return "undefined";
    }
}

std::string toString(SuperDataType t) {
    if (!t.type.has_value()) {
        return " of undefined type";
    }

    std::string str;

    if (t.isArray) {
        str += " is array";
    }

    str += " of type " + toString(t.type);

    return str;
}

std::string toString(StmtType t) {
    switch (t) {
    case StmtType::Break:
        return "Break";
    case StmtType::Compound:
        return "Compound";
    case StmtType::For:
        return "For";
    case StmtType::Range:
        return "Range";
    case StmtType::Return:
        return "Return";
    case StmtType::Select:
        return "If";
    case StmtType::While:
        return "While";
    default:
        return "Stmt";
    }
}

std::string toString(BoolOpType t) {
    switch (t) {
    case BoolOpType::And:
        return "and";
    case BoolOpType::Or:
        return "or";
    case BoolOpType::EQ:
        return "==";
    case BoolOpType::GEQ:
        return ">=";
    case BoolOpType::GT:
        return ">";
    case BoolOpType::LEQ:
        return "<=";
    case BoolOpType::LT:
        return "<";
    case BoolOpType::NEQ:
        return "!=";
    default:
        return "boolop";
    }
}

std::string toString(UnaryOpType t) {
    switch (t) {
    case UnaryOpType::Chsign:
        return "chsign";
    case UnaryOpType::Not:
        return "not";
    case UnaryOpType::Random:
        return "?";
    case UnaryOpType::Sizeof:
        return "sizeof";
    default:
        return "unaryop";
    }
}

std::string toString(UnaryAsgnType t) {
    switch (t) {
    case UnaryAsgnType::Dec:
        return "--";
    case UnaryAsgnType::Inc:
        return "++";
    default:
        return "unaryasgn";
    }
}

std::string toString(BinaryOpType t) {
    switch (t) {
    case BinaryOpType::Add:
        return "+";
    case BinaryOpType::Div:
        return "/";
    case BinaryOpType::Index:
        return "[";
    case BinaryOpType::Mod:
        return "%";
    case BinaryOpType::Mul:
        return "*";
    case BinaryOpType::Subtract:
        return "-";
    default:
        return "binaryop";
    }
}

std::string toString(AsgnType t) {
    switch (t) {
    case AsgnType::AddAsgn:
        return "+=";
    case AsgnType::Asgn:
        return "=";
    case AsgnType::DivAsgn:
        return "/=";
    case AsgnType::MulAsgn:
        return "*=";
    case AsgnType::SubAsgn:
        return "-=";
    default:
        return "asgn";
    }
}
} // namespace Tree::Types