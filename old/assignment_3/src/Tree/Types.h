#pragma once

#include <optional>
#include <string>

namespace Tree {
enum class DataType { Int, Bool, Char, Void };
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

struct SuperDataType {
    std::optional<DataType> type;
    bool isArray = false;
    bool isStatic = false;
    bool isConst = false;
};

namespace Types {
// these are for printing out the concrete type of a node. 
// these are necessary because there are slight differences between many different nodes
// for printing.
std::string toString(DataType);
std::string toString(std::optional<DataType>);
std::string toString(SuperDataType);
std::string toString(StmtType);
std::string toString(BoolOpType);
std::string toString(UnaryOpType);
std::string toString(UnaryAsgnType);
std::string toString(BinaryOpType);
std::string toString(AsgnType);
}
}