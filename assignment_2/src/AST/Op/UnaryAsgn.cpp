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

    UnaryAsgn::UnaryAsgn(unsigned lineNum)
        : Node::Node(lineNum)
    {
    }

    UnaryAsgn::UnaryAsgn(unsigned lineNum, Type type, Node *exp)
        : Node::Node(lineNum),
          m_type(type)
    {
        addChild(exp);
    }

    std::string UnaryAsgn::toString() const
    {
        return "Assign: " + s_typeToString.at(m_type) + lineTag();
    }
}
