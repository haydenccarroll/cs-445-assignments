#pragma once

#include <string>

namespace strutil
{
    std::string remove_quotes(std::string);
    int str_len(const std::string &);
    char get_char(const std::string &, int &);
    char get_first_char(const std::string &);
    std::string make_str(const std::string &);
}