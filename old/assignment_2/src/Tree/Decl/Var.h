#ifndef VAR_H
#define VAR_H

#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace Tree::Decl
{
    class Var : public Decl
    {
    public:
        // id  - name of variable
        // isArr - is var array
        Var(unsigned lineNum, const std::string &id, bool isArr);
        virtual std::string toString() const override;
        // Set var and all siblings to static.
        void setStatic();

    protected:
        bool _isArray = false;
        bool _isStatic = false;
    };
}

#endif