#include "Binary.h"
#include "../Node.h"

#include <map>
#include <string>
#include <stdexcept>

namespace Tree::Op
{
    const std::map<Binary::Type, std::string>
        Binary::_typeStringMap = {{Type::Add, "+"},
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

    Binary::Binary(unsigned lineNum, Type type, Node *exp1, Node *exp2)
        : Node::Node(lineNum),
          _type(type)
    {
        addChild(exp1);
        addChild(exp2);
    }

    void Binary::addChildren(Node *exp1, Node *exp2)
    {
        if (_children.size() >= 1)
        {
            if (_children[0] != nullptr && exp1 != nullptr)
            {
                throw std::runtime_error("Binary operator already has a first child!");
            }
            else
            {
                _children[0] = exp1;
            }
        }
        else
        {
            _children.push_back(exp1);
        }

        if (_children.size() >= 2)
        {
            if (_children[1] != nullptr && exp2 != nullptr)
            {
                throw std::runtime_error("Binary operator already has a second child!");
            }
            else
            {
                _children[1] = exp2;
            }
        }
        else
        {
            _children.push_back(exp2);
        }
    }

    std::string Binary::toString() const
    {
        return "Op: " + _typeStringMap.at(_type) + lineTag();
    }
}