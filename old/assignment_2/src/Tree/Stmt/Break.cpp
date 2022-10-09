#include "Break.h"
#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    Break::Break(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
        _type = DataType::Break;
    }
}