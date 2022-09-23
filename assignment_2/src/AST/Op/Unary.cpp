#include "Unary.h"
#include "../Node.h"

#include <map>
#include <string>
#include <stdexcept>

namespace AST::Op
{
    const std::map<Unary::Type, std::string>
        Unary::s_typeToString = {{Type::Chsign, "chsign"},
                                 {Type::Not, "not"},
                                 {Type::Random, "?"},
                                 {Type::Sizeof, "sizeof"}};

    Unary::Unary()
        : Node::Node()
    {
    }

    Unary::Unary(unsigned lineNum)
        : Node::Node(lineNum)
    {
    }

    Unary::Unary(unsigned lineNum, Type type, Node *exp)
        : Node::Node(lineNum),
          m_type(type)
    {
        addChild(exp);
    }

    void Unary::addExp(Node *exp)
    {
        if (m_children.size() > 0)
        {
            if (m_children[0] == nullptr)
            {
                m_children[0] = exp;
            }
            else
            {
                throw std::runtime_error("Unary operator cannot have more than one child.");
            }
        }
        else
        {
            addChild(exp);
        }
    }

    std::string Unary::toString() const
    {
        return "Op: " + s_typeToString.at(m_type) + lineTag();
    }
}