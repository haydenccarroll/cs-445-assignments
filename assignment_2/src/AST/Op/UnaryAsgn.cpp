#include "UnaryAsgn.h"
#include "../Node.h"

#include <map>
#include <string>

namespace AST::Op
{
    const std::map<UnaryAsgn::Type, std::string>
        UnaryAsgn::s_typeToString = {{Type::Dec, "--"},
                                     {Type::Inc, "++"}};

    UnaryAsgn::UnaryAsgn()
        : Node::Node()
    {
    }

    UnaryAsgn::UnaryAsgn(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    UnaryAsgn::UnaryAsgn(unsigned linenum, Type type, Node *exp)
        : Node::Node(linenum),
          m_type(type)
    {
        addChild(exp);
    }

    std::string UnaryAsgn::toString() const
    {
        return "Assign: " + s_typeToString.at(m_type) + lineTag();
    }
}