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

    For::For(unsigned linenum)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::For;
    }

    For::For(unsigned linenum, Node *id, Node *range, Node *stmt)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::For;
        addChild(id);
        addChild(range);
        addChild(stmt);
    }
}