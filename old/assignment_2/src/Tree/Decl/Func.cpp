#include "Func.h"
#include "../Node.h"
#include "Decl.h"

#include <string>
#include <map>

namespace Tree::Decl
{
    Func::Func(unsigned lineNum, const std::string &id,
               Node *parms, Node *compoundstmt)
        : Decl::Decl(lineNum)
    {
        _id = id;
        addChild(parms);
        addChild(compoundstmt);
    }

    Func::Func(unsigned lineNum, Type returnType, const std::string &id,
               Node *parms, Node *compoundstmt)
        : Decl::Decl(lineNum)
    {
        _type = returnType;
        _id = id;
        addChild(parms);
        addChild(compoundstmt);
    }

    std::string Func::toString() const
    {
        std::string str = "Func: " + _id + " returns type ";

        if (_type.has_value())
        {
            str += _typeStringMap.at(_type.value());
        }
        else
        {
            str += "void";
        }

        str += lineTag();
        return str;
    }
}