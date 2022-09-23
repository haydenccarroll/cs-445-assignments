#pragma once

#include "../Node.h"

#include <string>

namespace AST::Exp
{
    /// Identifier node
    class Id : public Node
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