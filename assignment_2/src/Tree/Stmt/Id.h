#ifndef ID_H
#define ID_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace Tree::Stmt
{
    class Id : public Stmt
    {
    public:
        Id(unsigned lineNum, const std::string &id);
        virtual std::string toString() const override;

    protected:
        std::string _id;
    };
}

#endif