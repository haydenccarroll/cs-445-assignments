#include "Range.h"
#include "../Node.h"

#include <string>

namespace AST::Exp
{
    Range::Range()
        : Node::Node()
    {
    }

    Range::Range(unsigned lineNum)
        : Node::Node(lineNum)
    {
    }

    Range::Range(unsigned lineNum, Node *from, Node *to, Node *by)
        : Node::Node(lineNum)
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