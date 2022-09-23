#include "Range.h"
#include "../Node.h"

#include <string>

namespace AST::Exp
{
    Range::Range()
        : Node::Node()
    {
    }

    Range::Range(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    Range::Range(unsigned linenum, Node *from, Node *to, Node *by)
        : Node::Node(linenum)
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