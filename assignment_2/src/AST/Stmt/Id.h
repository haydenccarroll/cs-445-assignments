#ifndef ID_H
#define ID_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class Id : public Stmt
    {
    public:
        Id();
        Id(unsigned lineNum);
        Id(unsigned lineNum, const std::string &id);
        virtual std::string toString() const override;

    protected:
        std::string m_id;
    };
}

#endif