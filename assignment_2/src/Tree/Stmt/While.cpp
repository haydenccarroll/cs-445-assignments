#include "While.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    While::While(unsigned lineNum, Node *exp, Node *stmt)
        : Stmt::Stmt(lineNum)
    {
        _type = DataType::While;
        addChild(exp);
        addChild(stmt);
    }
}