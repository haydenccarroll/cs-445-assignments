#include "Parm.h"
#include "../Node.h"

#include <map>
#include <string>

namespace AST::Decl
{
    Parm::Parm()
        : Decl::Decl()
    {
    }

    Parm::Parm(unsigned lineNum)
        : Decl::Decl(lineNum)
    {
    }

    Parm::Parm(unsigned lineNum, const std::string &id, bool isArray)
        : Decl::Decl(lineNum),
          m_isArray(isArray)
    {
        m_id = id;
    }

    std::string Parm::toString() const
    {
        std::string str = "Parm: " + m_id;
        if (m_isArray)
        {
            str += " of array";
        }
        str += " of type " + s_typeToString.at(m_type.value()) + lineTag();
        return str;
    }
}