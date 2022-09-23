#include "Stmt.h"
#include "../Node.h"

#include <map>
#include <string>

namespace AST::Stmt
{
    const std::map<Stmt::Type, std::string> Stmt::s_typeToString = {{Type::Break, "Break"},
                                                                    {Type::Compound, "Compound"},
                                                                    {Type::For, "For"},
                                                                    {Type::Return, "Return"},
                                                                    {Type::Select, "If"},
                                                                    {Type::While, "While"}};
    Stmt::Stmt()
        : Node::Node()
    {
    }

    Stmt::Stmt(unsigned linenum)
        : Node::Node(linenum)
    {
    }

    std::string Stmt::toString() const
    {
        return s_typeToString.at(m_type) + lineTag();
    }
}