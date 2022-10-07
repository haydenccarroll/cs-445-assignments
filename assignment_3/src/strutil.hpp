#pragma once

#include <string>

class strutil {
  public:
    static std::string remove_quotes(std::string);
    static std::string make_str(const std::string &);
    static char make_char(const std::string &);
    static char make_char(const std::string &, int linenumber);
    static int str_len(const std::string &);

  private:
    static char get_char(const std::string &, int &);
};