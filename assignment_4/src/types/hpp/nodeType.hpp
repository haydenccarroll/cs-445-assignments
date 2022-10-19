#pragma once

#include <string>

enum class NodeType
{
    AssignOpNode,
    BinaryOpNode,
    BreakNode,
    CallNode,
    CompoundStmtNode,
    ConstNode,
    ForNode,
    FunDeclNode,
    IdNode,
    IfNode,
    RangeNode,
    RelOpNode,
    ReturnNode,
    UnaryOpNode,
    VarDeclNode,
    WhileNode,
    ExpNode
};
