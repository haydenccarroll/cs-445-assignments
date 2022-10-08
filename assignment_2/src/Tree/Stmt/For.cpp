#include "For.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    For::For(unsigned lineNum, Node *id, Node *range, Node *stmt)
        : Stmt::Stmt(lineNum)
    {
        _type = DataType::For;
        addChild(id);
        addChild(range);
        addChild(stmt);
    }
}