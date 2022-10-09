#pragma once

#include <string>

namespace helpers {
std::string remove_quotes(std::string);
char make_char(const std::string &, int lineNumber);
char get_char(const std::string &, int &);
};