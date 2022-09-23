#ifndef PARM_H
#define PARM_H

#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace Tree::Decl
{
    class Parm : public Decl
    {
    public:
        // id - param name
        // isArr - is array
        Parm(unsigned lineNum, const std::string &id, bool isArr);
        virtual std::string toString() const override;

    protected:
        bool _isArray;
    };
}

#endif