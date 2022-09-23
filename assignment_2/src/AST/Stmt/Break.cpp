#include "Break.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    Break::Break()
        : Stmt::Stmt()
    {
        m_type = Type::Break;
    }

    Break::Break(unsigned linenum)
        : Stmt::Stmt(linenum)
    {
        m_type = Type::Break;
    }
}