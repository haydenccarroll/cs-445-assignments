#include <iostream>
#include <string>

#include "helpers.h"

namespace helpers
{
    std::string removeQuotes(std::string str)
    {
        return str.substr(1, str.size() - 2);
    }

    std::string toString(std::string str)
    {
        std::string cumString = "";
        for (int i=0; i < str.length(); i++) {
            if (str[i] == '\\' && i < str.length() - 1) {
                i++;
                switch (str[i]) {
                    case 'n':
                        cumString += '\n';
                        break;
                    case '0':
                        cumString += '\0';
                        break;
                    default:
                        cumString += str[i];
                }
            }
            else {
                cumString += str[i];
            }
        }
        return cumString;
    }

    char toChar(std::string str)
    {
        for (int i=0; i < str.length(); i++) {
            if (str[i] == '\\' && i < str.length() - 1) {
                i++;
                switch (str[i]) {
                    case 'n':
                        return '\n';
                    case '0':
                        return '\0';
                    default:
                        return str[i];
                }
            }
            else {
                return str[i];
            }
        }
        return '\0';
    }
}