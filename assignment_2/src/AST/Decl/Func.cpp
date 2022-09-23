#include "Func.h"
#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace AST::Decl
{
    Func::Func()
        : Decl::Decl()
    {
    }

    Func::Func(unsigned linenum)
        : Decl::Decl(linenum)
    {
    }

    Func::Func(unsigned linenum, const std::string &id,
               Node *parms, Node *compoundstmt)
        : Decl::Decl(linenum)
    {
        m_id = id;
        addChild(parms);
        addChild(compoundstmt);
    }

    Func::Func(unsigned linenum, Type returnType, const std::string &id,
               Node *parms, Node *compoundstmt)
        : Decl::Decl(linenum)
    {
        m_type = returnType;
        m_id = id;
        addChild(parms);
        addChild(compoundstmt);
    }

    std::string Func::toString() const
    {
        std::string str = "Func: " + m_id + " returns type ";

        if (m_type.has_value())
        {
            str += s_typeToString.at(m_type.value());
        }
        else
        {
            str += "void";
        }

        str += lineTag();
        return str;
    }
}