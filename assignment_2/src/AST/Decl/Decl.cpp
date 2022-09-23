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

    Decl::Decl(unsigned linenum)
        : Node::Node(linenum)
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