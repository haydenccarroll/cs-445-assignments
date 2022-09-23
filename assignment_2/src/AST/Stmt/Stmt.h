#ifndef STMT_H
#define STMT_H

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Stmt
{
    class Stmt : public Node
    {
    public:
        Stmt();
        Stmt(unsigned lineNum);
        virtual std::string toString() const override;

    protected:
        enum class Type
        {
            Break,
            Compound,
            For,
            Return,
            Select,
            While
        };

        static const std::map<Type, std::string> s_typeToString;
        Type m_type;
    };
}

#include "Break.h"
#include "Compound.h"
#include "For.h"
#include "Return.h"
#include "Select.h"
#include "While.h"
#include "Range.h"
#include "Id.h"
#include "Const.h"
#include "Call.h"

#endif