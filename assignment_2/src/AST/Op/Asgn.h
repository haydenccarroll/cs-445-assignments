#pragma once

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Op
{
    /// Assignment node
    class Asgn : public Node
    {
    public:
        /// Assignment types
        enum class Type
        {
            Asgn,
            AddAsgn,
            SubAsgn,
            DivAsgn,
            MulAsgn
        };

        Asgn();
        /// @param linenum Line number the node appears on
        Asgn(unsigned linenum);
        /// Children nodes are optional in the constructor, but they must be provided eventually!
        /// Use addChildren to add them later.
        /// @param linenum Line number the node appears on
        /// @param type Assignment type
        /// @param exp1 The assignee
        /// @param exp2 The expression assigned to exp1
        Asgn(unsigned linenum, Type type, Node *exp1 = nullptr, Node *exp2 = nullptr);
        /// @param exp1 The assignee
        /// @param exp2 The expression assigned to exp1
        void addChildren(Node *exp1, Node *exp2);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;

        Type m_type;
    };
}