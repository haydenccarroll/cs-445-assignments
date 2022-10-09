#ifndef RANGE_H
#define RANGE_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    class Range : public Stmt
    {
    public:
        // by - is optional, amount to increment by
        Range(unsigned lineNum, Node *from, Node *to, Node *by = nullptr);
        virtual std::string toString() const override;
    };
}

#endif