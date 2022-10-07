#pragma once

#include <optional>
#include <string>

namespace AST {
enum class Type { Int, Bool, Char, Void };
enum class NodeType { Decl, Exp, Stmt };
enum class StmtType { Break, Compound, For, Range, Return, Select, While };
enum class DeclType { Func, Parm, Var };
enum class ExpType { Call, Const, Id, Op };
enum class OpType { Unary, Binary };
enum class BoolOpType { LT, LEQ, GT, GEQ, EQ, NEQ, And, Or };
enum class UnaryOpType { Chsign, Sizeof, Random, Not, Asgn };
enum class UnaryAsgnType { Inc, Dec };
enum class BinaryOpType { Mul, Div, Mod, Add, Subtract, Bool, Index, Asgn };
enum class AsgnType { Asgn, AddAsgn, SubAsgn, DivAsgn, MulAsgn };

struct TypeInfo {
    std::optional<Type> type;
    bool isArray = false;
    bool isStatic = false;
    bool isConst = false;
};

namespace Types {
std::string toString(Type);
std::string toString(std::optional<Type>);
std::string toString(TypeInfo);
std::string toString(StmtType);
std::string toString(BoolOpType);
std::string toString(UnaryOpType);
std::string toString(UnaryAsgnType);
std::string toString(BinaryOpType);
std::string toString(AsgnType);
} // namespace Types
} // namespace AST