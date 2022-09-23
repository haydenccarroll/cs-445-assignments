#ifndef VAR_H
#define VAR_H

#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace AST::Decl
{
    class Var : public Decl
    {
    public:
        Var();
        Var(unsigned lineNum);
        // id  - name of variable
        // isArr - is var array
        Var(unsigned lineNum, const std::string &id, bool isArr);
        virtual std::string toString() const override;
        // Set var and all siblings to static.
        void setStatic();

    protected:
        bool m_isArray = false;
        bool m_isStatic = false;
    };
}

#endif