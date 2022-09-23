#include "Decl.h"
#include "../Node.h"

#include <string>
#include <map>

namespace Tree::Decl
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
        _type = type;
        if (_sibling != nullptr)
        {
            ((Decl *)_sibling)->setType(type);
        }
    }
}
