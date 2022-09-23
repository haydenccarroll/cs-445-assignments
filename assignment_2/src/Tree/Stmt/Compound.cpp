#include "Compound.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    Compound::Compound(unsigned lineNum, Node *localdecls, Node *stmtlist)
        : Stmt::Stmt(lineNum)
    {
        _type = Type::Compound;
        addChild(localdecls);
        addChild(stmtlist);
    }
}