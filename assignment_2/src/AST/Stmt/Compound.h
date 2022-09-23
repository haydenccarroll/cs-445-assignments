#ifndef COMPOUND_H
#define COMPOUND_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class Compound : public Stmt
    {
    public:
        Compound();
        Compound(unsigned lineNum);
        // localDecls - Local declarations, nullptr for none
        // stmtList -  Statement list, nullptr for none
        Compound(unsigned lineNum, Node *localDecls, Node *stmtList);
    };
}

#endif