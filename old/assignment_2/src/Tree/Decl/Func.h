#ifndef FUNC_H
#define FUNC_H

#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace Tree::Decl
{
    class Func : public Decl
    {
    public:
        // id - the function identifier (name of function)
        // parms - the function parameters
        // compoundstmt = compound statement of function (the curly braces stuff)
        Func(unsigned lineNum, const std::string &id, Node *parms, Node *compoundstmt);
        // type - return type of function
        // id - the function identifier (name of function)
        // parms - the function parameters
        // compoundstmt = compound statement of function (the curly braces stuff)
        Func(unsigned lineNum, Type type, const std::string &id, Node *parms, Node *compoundstmt);
        virtual std::string toString() const override;
    };
}

#endif
