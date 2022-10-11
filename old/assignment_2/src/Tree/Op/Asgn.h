#ifndef ASGN_H
#define ASGN_H

#include "../Node.h"

#include <map>
#include <string>

namespace Tree::Op
{
    class Asgn : public Node
    {
    public:
        enum class Type
        {
            DivAsgn,
            MulAsgn,
            Asgn,
            AddAsgn,
            SubAsgn
        };

        // although lval and rval are optional, they must be set. they can be set later by addChildren.
        // type - type of assignment (enum Type)
        // lval - lval of assignment
        // rval - rval of assignment
        Asgn(unsigned lineNum, Type type, Node *lval = nullptr, Node *rval = nullptr);
        void addChildren(Node *exp1, Node *exp2);
        virtual std::string toString() const override;

    protected:
        static const std::map<Type, std::string> _typeStringMap;
        Type _type;
    };
}

#endif