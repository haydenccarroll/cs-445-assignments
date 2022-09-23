#pragma once

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    /// Identifier node
    class Id : public Stmt
    {
    public:
        Id();
        /// @param lineNum Line number the node appears on
        Id(unsigned lineNum);
        /// @param lineNum Line number the node appears on
        /// @param id String identifier
        Id(unsigned lineNum, const std::string &id);
        virtual std::string toString() const override;

    protected:
        std::string m_id;
    };
}