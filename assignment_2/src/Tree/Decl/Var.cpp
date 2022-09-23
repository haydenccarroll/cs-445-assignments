#include "Var.h"
#include "../Node.h"
#include "Decl.h"

#include <map>
#include <string>

namespace Tree::Decl
{
    Var::Var(unsigned lineNum, const std::string &id, bool isArray)
        : Decl::Decl(lineNum),
          _isArray(isArray)
    {
        _id = id;
    }

    void Var::setStatic()
    {
        if (_sibling != nullptr) {
            ((Var* )_sibling)->setStatic();
        }
        
        _isStatic = true;
    }

    std::string Var::toString() const
    {
        std::string str = "Var: " + _id;
        if (_isArray)
        {
            str += " of array";
        }
        str += " of";
        if (_isStatic)
        {
            str += " static";
        }
        str += " type " + _typeStringMap.at(_type.value()) + lineTag();
        return str;
    }
}