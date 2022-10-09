#ifndef RETURN_H
#define RETURN_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    class Return : public Stmt
    {
    public:
        Return(unsigned lineNum, Node *exp);
    };
}

#endif