#include "Id.h"
#include "../Node.h"

#include <string>

namespace Tree::Stmt
{
    Id::Id(unsigned lineNum, const std::string &id)
        : Stmt::Stmt(lineNum),
          _id(id)
    {
    }

    std::string Id::toString() const
    {
        return "Id: " + _id + lineTag();
    }
}