#include "Compound.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    Compound::Compound()
        : Stmt::Stmt()
    {
        m_type = Type::Compound;
    }

    Compound::Compound(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::Compound;
    }

    Compound::Compound(unsigned lineNum, Node *localdecls, Node *stmtlist)
        : Stmt::Stmt(lineNum)
    {
        m_type = Type::Compound;
        addChild(localdecls);
        addChild(stmtlist);
    }
}