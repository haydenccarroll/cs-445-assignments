#ifndef DECL_H
#define DECL_H

#include "../Node.h"

#include <map>
#include <optional>
#include <string>

namespace AST::Decl
{
    // 3 different types of decls
    enum class Type
    {
        Bool,
        Int,
        Char
    };

    static const std::map<Type, std::string> s_typeToString = {{Type::Bool, "bool"},
                                                               {Type::Char, "char"},
                                                               {Type::Int, "int"}};
    ;

    /// Abstract base decl class inherits from node
    class Decl : public Node
    {
    public:
        Decl();
        Decl(unsigned lineNum);
        // Set the node and all its sibling's types to type.
        virtual void setType(Type type);

    protected:
        std::optional<Type> m_type;
        std::string m_id;
    };
}

#include "Func.h"
#include "Parm.h"
#include "Var.h"

#endif