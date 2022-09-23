#ifndef CONST_H
#define CONST_H

#include "../Node.h"
#include "Stmt.h"

#include <variant>

namespace Tree::Stmt
{
    class Const : public Stmt
    {
    public:
        enum class Type
        {
            Int,
            Bool,
            Char,
            String
        };
        // data - data of const in string form.
        Const(unsigned lineNum, Type type, std::string data);
        virtual std::string toString() const override;

    protected:
        char _toChar(std::string str) const;
        std::variant<int, bool, char, std::string> _value;
        Type _type;
    };
}

#endif