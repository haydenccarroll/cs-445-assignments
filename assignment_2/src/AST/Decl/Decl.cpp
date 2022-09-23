#include "Decl.h"
#include "../Node.h"

#include <map>
#include <string>

namespace AST::Decl
{
    Decl::Decl()
        : Node::Node()
    {
    }

    Decl::Decl(unsigned lineNum)
        : Node::Node(lineNum)
    {
    }

    void Decl::setType(Type type)
    {
        m_type = type;
        if (m_sibling != nullptr)
        {
            ((Decl *)m_sibling)->setType(type);
        }
    }
}
