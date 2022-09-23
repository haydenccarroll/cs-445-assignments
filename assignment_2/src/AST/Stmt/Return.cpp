#include "Return.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    Return::Return()
        : Stmt::Stmt()
    {
        m_type = Type::Return;
    }

    Return::Return(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::Return;
    }

    Return::Return(unsigned lineNum, Node *exp)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::Return;
        addChild(exp);
    }
}