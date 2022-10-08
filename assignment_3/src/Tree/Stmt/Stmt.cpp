#include "Stmt.h"
#include "../Node.h"
#include "../Types.h"

#include <map>
#include <string>

namespace Tree::Stmt {

Stmt::Stmt() : Node::Node() { m_nodeType = Tree::NodeType::Stmt; }

Stmt::Stmt(unsigned lineNum) : Node::Node(lineNum, Tree::NodeType::Stmt) {}

Stmt::Stmt(unsigned lineNum, StmtType stmtType)
    : Node::Node(lineNum, Tree::NodeType::Stmt) {
    m_stmtType = stmtType;
}

const StmtType &Stmt::stmtType() const { return m_stmtType; }

std::string Stmt::toString(bool debugging) const {
    return Types::toString(m_stmtType) + lineTag();
}

bool Stmt::is(StmtType t) const { return this != nullptr && m_stmtType == t; }
} // namespace Tree::Stmt