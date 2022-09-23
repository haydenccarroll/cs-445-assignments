#ifndef BINARY_H
#define BINARY_H

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Op
{
    class Binary : public Node
    {
    public:
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
        Binary(unsigned lineNum);
        // note: must add children either now or later.
        // type - type of operatr
        // lval - lval
        // rval - rval
        Binary(unsigned lineNum, Type type, Node *lval = nullptr, Node *rval = nullptr);
        // lval - lval
        // rval - rval
        void addChildren(Node *lval, Node *rval);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;
        Type m_type;
    };
}

#endif