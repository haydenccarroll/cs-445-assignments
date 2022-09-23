#include "UnaryAsgn.h"
#include "../Node.h"

#include <map>
#include <string>

namespace Tree::Op
{
    const std::map<UnaryAsgn::Type, std::string>
        UnaryAsgn::_typeStringMap = {{Type::Dec, "--"},
                                     {Type::Inc, "++"}};

    UnaryAsgn::UnaryAsgn(unsigned lineNum, Type type, Node *exp)
        : Node::Node(lineNum),
          _type(type)
    {
        addChild(exp);
    }

    std::string UnaryAsgn::toString() const
    {
        return "Assign: " + _typeStringMap.at(_type) + lineTag();
    }
}
