#include "Stmt.hpp"
#include "../Node.hpp"
#include "../Types.hpp"

#include <map>
#include <string>

namespace AST::Stmt {

Stmt::Stmt() : Node::Node() { m_nodeType = AST::NodeType::Stmt; }

Stmt::Stmt(unsigned linenum) : Node::Node(linenum, AST::NodeType::Stmt) {}

Stmt::Stmt(unsigned linenum, StmtType stmtType)
    : Node::Node(linenum, AST::NodeType::Stmt) {
    m_stmtType = stmtType;
}

const StmtType &Stmt::stmtType() const { return m_stmtType; }

std::string Stmt::toString(bool debugging) const {
    return Types::toString(m_stmtType) + lineTag();
}

bool Stmt::is(StmtType t) const { return this != nullptr && m_stmtType == t; }
} // namespace AST::Stmt