#include "Call.h"
#include "../Node.h"

#include <string>

namespace AST::Stmt
{
    Call::Call()
        : Stmt::Stmt()
    {
    }

    Call::Call(unsigned lineNum)
        : Stmt::Stmt(lineNum)
    {
    }

    Call::Call(unsigned lineNum, const std::string &id, Node *arglist)
        : Stmt::Stmt(lineNum),
          m_id(id)
    {
        addChild(arglist);
    }

    std::string Call::toString() const
    {
        return "Call: " + m_id + lineTag();
    }
}