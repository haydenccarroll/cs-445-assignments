#include "Select.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    Select::Select(unsigned lineNum, Node *exp, Node *stmt1, Node *stmt2)
        : Stmt::Stmt(lineNum)
    {
        _type = Type::Select;
        addChild(exp);
        addChild(stmt1);
        addChild(stmt2);
    }
}