#include "Select.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    Select::Select()
        : Stmt::Stmt()
    {
        m_type = Type::Select;
    }

    Select::Select(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::Select;
    }

    Select::Select(unsigned lineNum, Node *exp, Node *stmt1, Node *stmt2)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::Select;
        addChild(exp);
        addChild(stmt1);
        addChild(stmt2);
    }
}