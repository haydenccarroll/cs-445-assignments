#ifndef FOR_H
#define FOR_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class For : public Stmt
    {
    public:
        For();
        For(unsigned lineNum);
        // id - name of iterator var
        // range - iter range
        // stmt - stmt of loop to be executed
        For(unsigned lineNum, Node *id, Node *range, Node *stmt);
    };
}

#endif