#ifndef BREAK_H
#define BREAK_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class Break : public Stmt
    {
    public:
        Break();
        Break(unsigned lineNum);
    };
}

#endif