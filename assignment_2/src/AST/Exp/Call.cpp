#include "Call.h"
#include "../Node.h"

#include <string>

namespace AST::Exp
{
    Call::Call()
        : Node::Node()
    {
    }

    Call::Call(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    Call::Call(unsigned linenum, const std::string &id, Node *arglist)
        : Node::Node(linenum),
          m_id(id)
    {
        addChild(arglist);
    }

    std::string Call::toString() const
    {
        return "Call: " + m_id + lineTag();
    }
}