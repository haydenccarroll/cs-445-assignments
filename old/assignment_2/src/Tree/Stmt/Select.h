#ifndef SELECT_H
#define SELECT_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    class Select : public Stmt
    {
    public:
        // exp - expression inside select
        // stmt1 - executed if exp is true
        // stmt2 - executed if exp is fales (else part, optional)
        Select(unsigned lineNum, Node *exp, Node *stmt1, Node *stmt2 = nullptr);
    };
}

#endif