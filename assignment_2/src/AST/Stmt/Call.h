#ifndef CALL_H
#define CALL_H

#include "../Node.h"
#include "Stmt.h"

#include <string>

namespace AST::Stmt
{
    class Call : public Stmt
    {
    public:
        Call();
        Call(unsigned lineNum);
        // id  - function name
        // arglist - optional arg list for func call
        Call(unsigned lineNum, const std::string &id, Node *arglist = nullptr);
        virtual std::string toString() const override;

    protected:
        std::string m_id;
    };
}

#endif