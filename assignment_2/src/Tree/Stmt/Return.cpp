#include "Return.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    Return::Return(unsigned lineNum, Node *exp)
        : Stmt::Stmt(lineNum)
    {
        _type = Type::Return;
        addChild(exp);
    }
}