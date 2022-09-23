#include "Range.h"
#include "../Node.h"

#include <string>

namespace AST::Stmt
{
    Range::Range()
        : Stmt::Stmt()
    {
    }

    Range::Range(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
    }

    Range::Range(unsigned lineNum, Node *from, Node *to, Node *by)
        : Stmt::Stmt(lineNum)
    {
        addChild(from);
        addChild(to);
        addChild(by);
    }

    std::string Range::toString() const
    {
        return "Range" + lineTag();
    }
}