#include "Unary.h"
#include "../Node.h"

#include <map>
#include <string>
#include <stdexcept>

namespace Tree::Op
{
    const std::map<Unary::Type, std::string>
        Unary::_typeStringMap = {{Type::Chsign, "chsign"},
                                 {Type::Not, "not"},
                                 {Type::Random, "?"},
                                 {Type::Sizeof, "sizeof"}};

    Unary::Unary(unsigned lineNum, Type type, Node *exp)
        : Node::Node(lineNum),
          _type(type)
    {
        addChild(exp);
    }

    void Unary::addExp(Node *exp)
    {
        if (_children.size() > 0)
        {
            if (_children[0] == nullptr)
            {
                _children[0] = exp;
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
        return "Op: " + _typeStringMap.at(_type) + lineTag();
    }
}