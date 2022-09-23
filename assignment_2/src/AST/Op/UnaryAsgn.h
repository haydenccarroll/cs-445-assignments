#pragma once

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Op
{
    /// Unary assignment operator
    class UnaryAsgn : public Node
    {
    public:
        /// Assignment type
        enum class Type
        {
            Inc,
            Dec
        };

        UnaryAsgn();
        /// @param linenum Line number the node appears on
        UnaryAsgn(unsigned linenum);
        /// @param linenum Line number the node appears on
        /// @param type Assignment type
        /// @param exp The node being assigned
        UnaryAsgn(unsigned linenum, Type type, Node *exp);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}