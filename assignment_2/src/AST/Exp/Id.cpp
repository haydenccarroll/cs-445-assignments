#include "Id.h"
#include "../Node.h"

#include <string>

namespace AST::Exp
{
    Id::Id()
        : Node::Node()
    {
    }

    Id::Id(unsigned lineNum)
        : Node::Node(lineNum)
    {
    }

    Id::Id(unsigned lineNum, const std::string &id)
        : Node::Node(lineNum),
          m_id(id)
    {
    }

    std::string Id::toString() const
    {
        return "Id: " + m_id + lineTag();
    }
}