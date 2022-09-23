#include "Call.h"
#include "../Node.h"

#include <string>

namespace Tree::Stmt
{
    Call::Call(unsigned lineNum, const std::string &id, Node *arglist)
        : Stmt::Stmt(lineNum),
          _id(id)
    {
        addChild(arglist);
    }

    std::string Call::toString() const
    {
        return "Call: " + _id + lineTag();
    }
}