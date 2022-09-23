#ifndef PARM_H
#define PARM_H

#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace AST::Decl
{
    class Parm : public Decl
    {
    public:
        Parm();
        Parm(unsigned lineNum);
        // id - param name
        // isArr - is array
        Parm(unsigned lineNum, const std::string &id, bool isArr);
        virtual std::string toString() const override;

    protected:
        bool m_isArray;
    };
}

#endif