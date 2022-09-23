#ifndef UNARY_H
#define UNARY_H

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Op
{
    class Unary : public Node
    {
    public:
        enum class Type
        {
            Chsign,
            Sizeof,
            Random,
            Not
        };

        Unary();
        Unary(unsigned lineNum);
        // note: must set exp now or later.
        // type - type of unary op
        // exp - exp op is used on. optional (must be set later)
        Unary(unsigned lineNum, Type type, Node *exp = nullptr);
        void addExp(Node *exp);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;
        Type m_type;
    };
}

#endif