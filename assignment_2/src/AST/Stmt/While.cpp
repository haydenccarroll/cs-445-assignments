#include "While.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    While::While()
        : Stmt::Stmt()
    {
        m_type = Type::While;
    }

    While::While(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::While;
    }

    While::While(unsigned lineNum, Node *exp, Node *stmt)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::While;
        addChild(exp);
        addChild(stmt);
    }
}