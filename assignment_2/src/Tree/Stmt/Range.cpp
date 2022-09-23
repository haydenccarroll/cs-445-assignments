#include "Range.h"
#include "../Node.h"

#include <string>

namespace Tree::Stmt
{
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