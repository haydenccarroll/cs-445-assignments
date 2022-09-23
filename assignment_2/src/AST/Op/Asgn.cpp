#include "Asgn.h"
#include "../Node.h"

#include <map>
#include <string>
#include <stdexcept>

namespace AST::Op
{
    const std::map<Asgn::Type, std::string>
        Asgn::s_typeToString = {{Type::AddAsgn, "+="},
                                {Type::Asgn, "="},
                                {Type::DivAsgn, "/="},
                                {Type::MulAsgn, "*="},
                                {Type::SubAsgn, "-="}};

    Asgn::Asgn()
        : Node::Node()
    {
    }

    Asgn::Asgn(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    Asgn::Asgn(unsigned linenum, Type type, Node *exp1, Node *exp2)
        : Node::Node(linenum),
          m_type(type)
    {
        addChild(exp1);
        addChild(exp2);
    }

    void Asgn::addChildren(Node *exp1, Node *exp2)
    {
        if (m_children.size() >= 1)
        {
            if (m_children[0] != nullptr && exp1 != nullptr)
            {
                throw std::runtime_error("Binary operator already has a first child!");
            }
            else
            {
                m_children[0] = exp1;
            }
        }
        else
        {
            m_children.push_back(exp1);
        }

        if (m_children.size() >= 2)
        {
            if (m_children[1] != nullptr && exp2 != nullptr)
            {
                throw std::runtime_error("Binary operator already has a second child!");
            }
            else
            {
                m_children[1] = exp2;
            }
        }
        else
        {
            m_children.push_back(exp2);
        }
    }

    std::string Asgn::toString() const
    {
        return "Assign: " + s_typeToString.at(m_type) + lineTag();
    }
}