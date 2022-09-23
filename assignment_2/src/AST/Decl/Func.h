#pragma once

#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace AST::Decl
{
    /// Function declaration node
    class Func : public Decl
    {
    public:
        Func();
        /// @param lineNum Line number the node appears on
        Func(unsigned lineNum);
        /// Function type is set to void
        /// @param lineNum Line number the node appears on
        /// @param id Function identifier
        /// @param parms Function parameters
        /// @param compoundstmt Function body
        Func(unsigned lineNum, const std::string &id, Node *parms, Node *compoundstmt);
        /// @param lineNum Line number the node appears on
        /// @param type Function return type
        /// @param id Function identifier
        /// @param parms Function parameters
        /// @param compoundstmt Function body
        Func(unsigned lineNum, Type type, const std::string &id, Node *parms, Node *compoundstmt);
        virtual std::string toString() const override;
    };
}