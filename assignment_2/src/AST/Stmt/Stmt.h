#pragma once

#include "../Node.h"

#include <map>
#include <string>

namespace AST::Stmt
{
    /// Base statement node
    class Stmt : public Node
    {
    public:
        Stmt();
        /// @param lineNum Line number the node appears on
        Stmt(unsigned lineNum);
        virtual std::string toString() const override;

    protected:
        /// Statement type (for printing)
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
