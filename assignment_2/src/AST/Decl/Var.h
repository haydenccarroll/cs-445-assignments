#pragma once

#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace AST::Decl
{
    /// Variable declaration node
    class Var : public Decl
    {
    public:
        Var();
        /// @param lineNum Line number the node appears on
        Var(unsigned lineNum);
        /// @param lineNum Line number the node appears on
        /// @param id String identifier
        /// @param isArray Whether or not the variable is an array
        Var(unsigned lineNum, const std::string &id, bool isArray);
        virtual std::string toString() const override;
        /// Set the variable and its siblings to static
        void setStatic();

    protected:
        bool m_isArray = false;
        bool m_isStatic = false;
    };
}