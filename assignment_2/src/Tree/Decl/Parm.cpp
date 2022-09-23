#include "Parm.h"
#include "../Node.h"

#include <map>
#include <string>

namespace Tree::Decl
{
    Parm::Parm(unsigned lineNum, const std::string &id, bool isArray)
        : Decl::Decl(lineNum),
          _isArray(isArray)
    {
        _id = id;
    }

    std::string Parm::toString() const
    {
        std::string str = "Parm: " + _id;
        if (_isArray)
        {
            str += " of array";
        }
        str += " of type " + _typeStringMap.at(_type.value()) + lineTag();
        return str;
    }
}