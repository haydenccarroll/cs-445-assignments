#ifndef BREAK_H
#define BREAK_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    class Break : public Stmt
    {
    public:
        Break(unsigned lineNum);
    };
}

#endif