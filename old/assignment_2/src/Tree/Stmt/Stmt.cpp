#include "Stmt.h"
#include "../Node.h"

#include <map>
#include <string>

namespace Tree::Stmt
{
    const std::map<Stmt::Type, std::string> Stmt::_typeStringMap = {{Type::Break, "Break"},
                                                                    {Type::Compound, "Compound"},
                                                                    {Type::For, "For"},
                                                                    {Type::Return, "Return"},
                                                                    {Type::Select, "If"},
                                                                    {Type::While, "While"}};
    Stmt::Stmt()
        : Node::Node()
    {
    }

    Stmt::Stmt(unsigned lineNum)
        : Node::Node(lineNum)
    {
    }

    std::string Stmt::toString() const
    {
        return _typeStringMap.at(_type) + lineTag();
    }
}