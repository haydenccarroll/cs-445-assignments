#ifndef RETURN_H
#define RETURN_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class Return : public Stmt
    {
    public:
        Return();
        Return(unsigned lineNum, Node *exp);
        Return(unsigned lineNum);
    };
}

#endif