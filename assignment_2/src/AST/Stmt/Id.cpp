#include "Id.h"
#include "../Node.h"

#include <string>

namespace AST::Stmt
{
    Id::Id()
        : Stmt::Stmt()
    {
    }

    Id::Id(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
    }

    Id::Id(unsigned lineNum, const std::string &id)
        : Stmt::Stmt(lineNum),
          m_id(id)
    {
    }

    std::string Id::toString() const
    {
        return "Id: " + m_id + lineTag();
    }
}