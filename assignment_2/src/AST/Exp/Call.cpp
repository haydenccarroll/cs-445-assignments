#include "Call.h"
#include "../Node.h"

#include <string>

namespace AST::Exp
{
    Call::Call()
        : Node::Node()
    {
    }

    Call::Call(unsigned lineNum)
        : Node::Node(lineNum)
    {
    }

    Call::Call(unsigned lineNum, const std::string &id, Node *arglist)
        : Node::Node(lineNum),
          m_id(id)
    {
        addChild(arglist);
    }

    std::string Call::toString() const
    {
        return "Call: " + m_id + lineTag();
    }
}