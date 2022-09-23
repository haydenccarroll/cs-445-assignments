#include "For.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    For::For()
        : Stmt::Stmt()
    {
        m_type = Type::For;
    }

    For::For(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::For;
    }

    For::For(unsigned lineNum, Node *id, Node *range, Node *stmt)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::For;
        addChild(id);
        addChild(range);
        addChild(stmt);
    }
}