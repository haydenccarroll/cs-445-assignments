#ifndef FOR_H
#define FOR_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    class For : public Stmt
    {
    public:
        // id - name of iterator var
        // range - iter range
        // stmt - stmt of loop to be executed
        For(unsigned lineNum, Node *id, Node *range, Node *stmt);
    };
}

#endif