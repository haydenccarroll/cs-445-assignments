#include "Id.h"
#include "../Node.h"

#include <string>

namespace AST::Exp
{
    Id::Id()
        : Node::Node()
    {
    }

    Id::Id(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    Id::Id(unsigned linenum, const std::string &id)
        : Node::Node(linenum),
          m_id(id)
    {
    }

    std::string Id::toString() const
    {
        return "Id: " + m_id + lineTag();
    }
}