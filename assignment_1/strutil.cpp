#include <iostream>
#include <string>

#include "strutil.hpp"

namespace strutil
{
    std::string remove_quotes(std::string s)
    {
        return s.erase(0, 1).erase(s.length() - 1, s.length());
    }

    int str_len(const std::string &s)
    {
        int counter = 0;
        for (unsigned i = 0; i < s.length(); i++)
        {
            if (s[i] == '\\')
            {
                if (i == s.length() - 1)
                {
                    return counter;
                }
                else
                {
                    i++;
                }
            }
            counter++;
        }

        return counter;
    }

    char get_char(const std::string &s, int &index)
    {
        if (index >= s.length())
        {
            std::cerr << "getChar(): index out of bounds\n";
            exit(EXIT_FAILURE);
        }

        char c = '\0';

        if (s[index] == '\\')
        {
            if (s.length() - index > 1)
            {
                switch (s[index + 1])
                {
                case 'n':
                    c = '\n';
                    break;
                case '0':
                    c = '\0';
                    break;
                default:
                    c = s[index + 1];
                    break;
                }
            }
            index += 2;
        }
        else
        {
            c = s[index];
            index++;
        }
        return c;
    }

    char get_first_char(const std::string &str)
    {
        int i = 0;
        return get_char(str, i);
    }

    std::string make_str(const std::string &str)
    {
        std::string str2;
        for (int i = 0; i < str.length();)
        {
            str2 += get_char(str, i);
        }
        return str2;
    }
}