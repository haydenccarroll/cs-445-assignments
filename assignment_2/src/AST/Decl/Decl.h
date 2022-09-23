#pragma once

#include "../Node.h"

#include <map>
#include <optional>
#include <string>

/// Namespace for declaration nodes
namespace AST::Decl
{
    /// Declaration type
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

    /// Base declaration node
    class Decl : public Node
    {
    public:
        Decl();
        /// @param lineNum Line number the node appears on
        Decl(unsigned lineNum);
        /// Set the node and its sibling's types to the provided type
        /// @param type Type to set
        virtual void setType(Type type);

    protected:
        std::optional<Type> m_type;
        std::string m_id;
    };
}

#include "Func.h"
#include "Parm.h"
#include "Var.h"