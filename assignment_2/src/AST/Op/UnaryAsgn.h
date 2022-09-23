#ifndef UNARYASGN_H
#define UNARYASGN_H

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Op
{
    class UnaryAsgn : public Node
    {
    public:
        enum class Type
        {
            Inc,
            Dec
        };

        UnaryAsgn();
        UnaryAsgn(unsigned lineNum);
        // type - Assignment type
        // exp  - exression to be incremented/decremented.
        UnaryAsgn(unsigned lineNum, Type type, Node *exp);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> s_typeToString;
        Type m_type;
    };
}

#endif