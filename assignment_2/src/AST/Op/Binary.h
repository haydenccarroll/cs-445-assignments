#pragma once

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Op
{
    /// Generic class for binary operator nodes
    /// "Generic" as in one-size-fits-all, not using generics or templates.
    class Binary : public Node
    {
    public:
        /// Binary operators
        enum class Type
        {
            Mul,
            Div,
            Mod,
            Add,
            Subtract,
            LT,
            LEQ,
            GT,
            GEQ,
            EQ,
            NEQ,
            And,
            Or,
            Index
        };

        Binary();
        /// @param linenum Line number the node appears on
        Binary(unsigned linenum);
        /// exp1 and exp2 are optional arguments, but they must be set later if not provided in the constructor!
        /// Set them with addChildren
        /// @param linenum Line number the node appears on
        /// @param type Operator type
        /// @param exp1 First argument
        /// @param exp2 Second argument
        Binary(unsigned linenum, Type type, Node *exp1 = nullptr, Node *exp2 = nullptr);
        /// @param exp1 First argument
        /// @param exp2 Second argument
        void addChildren(Node *exp1, Node *exp2);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}