#include <iostream>
#include <string>

#include "helpers.h"

namespace helpers
{
    std::string remove_quotes(std::string s)
    {
        return s.substr(1, s.size() - 2);
    }
}