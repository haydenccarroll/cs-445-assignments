#pragma once

#include "../Node.h"

#include <variant>

namespace AST::Exp
{
    /// Node for constants
    class Const : public Node
    {
    public:
        /// Constant types
        enum class Type
        {
            Int,
            Bool,
            Char,
            String
        };

        Const();
        /// @param linenum Line number the node appears on
        Const(unsigned linenum);
        /// @param linenum Line number the node appears on
        /// @param Type Type of the constant
        /// @param data String value of the data
        Const(unsigned linenum, Type type, std::string data);
        virtual std::string toString() const override;

    protected:

        std::variant<int, bool, char, std::string> m_value;
        Type m_type;
    };
}