#ifndef WHILE_H
#define WHILE_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class While : public Stmt
    {
    public:
        While();
        While(unsigned lineNum);
        // exp - exp of while loop
        // stmt - inside body statements to be executed in loop
        While(unsigned lineNum, Node *exp, Node *stmt);
    };
}

#endif