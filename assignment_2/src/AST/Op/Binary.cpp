#include "Binary.h"
#include "../Node.h"

#include <map>
#include <string>
#include <stdexcept>

namespace AST::Op
{
    const std::map<Binary::Type, std::string>
        Binary::s_typeToString = {{Type::Add, "+"},
                                  {Type::And, "and"},
                                  {Type::Div, "/"},
                                  {Type::EQ, "=="},
                                  {Type::GEQ, ">="},
                                  {Type::GT, ">"},
                                  {Type::Index, "["},
                                  {Type::LEQ, "<="},
                                  {Type::LT, "<"},
                                  {Type::Mod, "%"},
                                  {Type::Mul, "*"},
                                  {Type::NEQ, "!="},
                                  {Type::Or, "or"},
                                  {Type::Subtract, "-"}};

    Binary::Binary()
        : Node::Node()
    {
    }

    Binary::Binary(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    Binary::Binary(unsigned linenum, Type type, Node *exp1, Node *exp2)
        : Node::Node(linenum),
          m_type(type)
    {
        addChild(exp1);
        addChild(exp2);
    }

    void Binary::addChildren(Node *exp1, Node *exp2)
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

    std::string Binary::toString() const
    {
        return "Op: " + s_typeToString.at(m_type) + lineTag();
    }
}